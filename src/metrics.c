#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "metrics.h"
#include "helpers.h"

// =========================
// Implementación de métricas
// =========================

// Recorre todas las órdenes y agrupa las pizzas por su nombre.
// Se acumula la cantidad total vendida por tipo de pizza.
// Finalmente, se identifica cuál(es) tuvo la mayor cantidad de ventas
// y se devuelve una cadena con todas las que compartan ese máximo.
char* pms(int* size, Order* orders) {
    if (*size == 0 || orders == NULL) return strdup("Pizza más vendida: Sin datos");

    // Struct auxiliar para llevar conteo por nombre de pizza
    typedef struct {
        char nombre[128];
        int cantidad;
    } Conteo;

    Conteo* conteos = malloc(sizeof(Conteo) * (*size));
    int num_pizzas = 0;

    // Agrupar pizzas y contar
    for (int i = 0; i < *size; i++) {
        char* actual = orders[i].pizza_name;
        int cantidad = orders[i].quantity;
        int encontrado = 0;

        // Buscar si ya fue registrada
        for (int j = 0; j < num_pizzas; j++) {
            if (strcmp(conteos[j].nombre, actual) == 0) {
                conteos[j].cantidad += cantidad;
                encontrado = 1;
                break;
            }
        }

        // Si no existe, se agrega
        if (!encontrado) {
            memset(&conteos[num_pizzas], 0, sizeof(Conteo));
            strncpy(conteos[num_pizzas].nombre, actual, sizeof(conteos[num_pizzas].nombre) - 1);
            conteos[num_pizzas].cantidad = cantidad;
            num_pizzas++;
        }
    }

    // Obtener la mayor cantidad
    int max_cantidad = 0;
    for (int i = 0; i < num_pizzas; i++) {
        if (conteos[i].cantidad > max_cantidad) {
            max_cantidad = conteos[i].cantidad;
        }
    }

    // Construir string de resultado
    char pizzas[512] = "";
    for (int i = 0; i < num_pizzas; i++) {
        if (conteos[i].cantidad == max_cantidad) {
            if (strlen(pizzas) > 0) strcat(pizzas, ", ");
            strcat(pizzas, conteos[i].nombre);
        }
    }

    char* resultado = malloc(1024);
    snprintf(resultado, 1024, "Pizza más vendida: %s", pizzas);

    free(conteos);
    return resultado;
}


// Pizza menos vendida
// Misma lógica que pms, pero identifica la menor cantidad vendida.
char* pls(int* size, Order* orders) {
    if (*size == 0 || orders == NULL) return strdup("Pizza menos vendida: Sin datos");

    typedef struct {
        char nombre[128];
        int cantidad;
    } Conteo;

    Conteo* conteos = malloc(sizeof(Conteo) * (*size));
    int num_pizzas = 0;

    for (int i = 0; i < *size; i++) {
        char* actual = orders[i].pizza_name;
        int cantidad = orders[i].quantity;
        int encontrado = 0;

        for (int j = 0; j < num_pizzas; j++) {
            if (strcmp(conteos[j].nombre, actual) == 0) {
                conteos[j].cantidad += cantidad;
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            memset(&conteos[num_pizzas], 0, sizeof(Conteo));
            strncpy(conteos[num_pizzas].nombre, actual, sizeof(conteos[num_pizzas].nombre) - 1);
            conteos[num_pizzas].cantidad = cantidad;
            num_pizzas++;
        }
    }

    int min_cantidad = __INT_MAX__;
    for (int i = 0; i < num_pizzas; i++) {
        if (conteos[i].cantidad < min_cantidad) {
            min_cantidad = conteos[i].cantidad;
        }
    }

    char pizzas[512] = "";
    for (int i = 0; i < num_pizzas; i++) {
        if (conteos[i].cantidad == min_cantidad) {
            if (strlen(pizzas) > 0) strcat(pizzas, ", ");
            strcat(pizzas, conteos[i].nombre);
        }
    }

    char* resultado = malloc(1024);
    snprintf(resultado, 1024, "Pizza menos vendida: %s", pizzas);

    free(conteos);
    return resultado;
}
// Fecha con más ventas (en dinero)
// Recorre todas las órdenes y agrupa las ventas por fecha (usando la función auxiliar agrupar_fechas_unicas).
// Para cada fecha, calcula la suma del total_price de todas las órdenes de ese día.
// Guarda la fecha que tuvo la mayor suma total de dinero recaudado.
// Devuelve un string indicando la fecha y el monto correspondiente.

char* dms(int* size, Order* orders) {
    // Validación básica de datos de entrada
    if (*size == 0 || orders == NULL) return strdup("Sin datos");

    // Esta variable almacenará cuántas fechas únicas se encontraron
    int num_fechas = 0;

    // Agrupa las fechas únicas encontradas en el arreglo de órdenes
    // Esto permite evitar comparar todas las fechas directamente
    FechaAgrupada* fechas = agrupar_fechas_unicas(orders, *size, &num_fechas);

    // Si no se encontraron fechas únicas (lo que sería extraño), se retorna mensaje
    if (num_fechas == 0) {
        free(fechas); // Importante liberar memoria antes de retornar
        return strdup("Sin fechas agrupadas.");
    }

    float max_total = 0.0;         // Aquí guardamos el total más alto encontrado
    char fecha_max[16] = "";       // Guardaremos la fecha con mayores ventas

    // Recorremos cada fecha única
    for (int i = 0; i < num_fechas; i++) {
        float suma = 0.0;

        // Por cada fecha, recorremos todas las órdenes para ver cuáles coinciden
        for (int j = 0; j < *size; j++) {
            if (strcmp(fechas[i].fecha, orders[j].order_date) == 0) {
                suma += orders[j].total_price; // Sumamos el total vendido ese día
            }
        }

        // Si esa suma es mayor a la actual máxima, la actualizamos
        if (suma > max_total) {
            max_total = suma;
            strncpy(fecha_max, fechas[i].fecha, sizeof(fecha_max) - 1);
            // strncpy se usa en vez de strcpy por seguridad (evita buffer overflow)
        }
    }

    // Creamos string de salida para el mensaje final
    char* resultado = malloc(128);
    snprintf(resultado, 128, "La fecha con más ventas es: %s con $%.2f", fecha_max, max_total);

    free(fechas); // Liberamos memoria asignada por agrupar_fechas_unicas

    return resultado; // Retornamos el mensaje con la respuesta
}

// Fecha con menos ventas (en dinero)
// Misma logica que dms, pero devuelve la fecha con el día menos vendido y el monto
char* dls(int* size, Order* orders) {
    if (*size == 0 || orders == NULL) return strdup("Sin datos");

    int num_fechas = 0;
    FechaAgrupada* fechas = agrupar_fechas_unicas(orders, *size, &num_fechas);

    if (num_fechas == 0) {
        free(fechas);
        return strdup("Sin fechas agrupadas.");
    }

    float min_total = __FLT_MAX__;
    char fecha_min[16] = "";

    for (int i = 0; i < num_fechas; i++) {
        float suma = 0.0;
        for (int j = 0; j < *size; j++) {
            if (strcmp(fechas[i].fecha, orders[j].order_date) == 0) {
                suma += orders[j].total_price;
            }
        }

        if (suma < min_total) {
            min_total = suma;
            strncpy(fecha_min, fechas[i].fecha, sizeof(fecha_min) - 1);
        }
    }

    char* resultado = malloc(128);
    snprintf(resultado, 128, "La fecha con menos ventas es: %s con $%.2f", fecha_min, min_total);

    free(fechas);
    return resultado;
}

// Fecha con menos ventas (cantidad de pizzas)
// Recorre todas las órdenes y agrupa las fechas únicas usando agrupar_fechas_unicas.
// Para cada fecha, calcula la suma de pizzas vendidas (quantity).
// Identifica la fecha con la menor cantidad de pizzas vendidas.
// Retorna un string con esa fecha y la cantidad correspondiente.

char* dlsp(int* size, Order* orders) {
    // Validación inicial para asegurar que haya datos
    if (*size == 0 || orders == NULL) return strdup("Sin datos");

    int num_fechas = 0;

    // Se obtienen las fechas únicas desde las órdenes
    FechaAgrupada* fechas = agrupar_fechas_unicas(orders, *size, &num_fechas);

    // Si no hay fechas únicas, se libera memoria y retorna mensaje
    if (num_fechas == 0) {
        free(fechas);
        return strdup("Sin fechas agrupadas.");
    }

    int min_cantidad = __INT_MAX__;   // Usamos el valor entero más alto posible para comenzar comparación
    char fecha_min[16] = "";          // Guardará la fecha con la menor cantidad de pizzas

    // Recorremos cada fecha única para contar cuántas pizzas se vendieron ese día
    for (int i = 0; i < num_fechas; i++) {
        int suma = 0;

        // Sumamos todas las cantidades (quantity) para la fecha actual
        for (int j = 0; j < *size; j++) {
            if (strcmp(fechas[i].fecha, orders[j].order_date) == 0) {
                suma += orders[j].quantity;
            }
        }

        // Si la suma de esa fecha es menor a la mínima actual, actualizamos
        if (suma < min_cantidad) {
            min_cantidad = suma;
            strncpy(fecha_min, fechas[i].fecha, sizeof(fecha_min) - 1);
        }
    }

    // Reservamos memoria para construir el mensaje de resultado
    char* resultado = malloc(128);
    snprintf(resultado, 128, "La fecha con menos pizzas vendidas es: %s con %d unidades", fecha_min, min_cantidad);

    free(fechas); // Liberamos memoria de fechas agrupadas
    return resultado;
}


// Promedio de pizzas por orden
// Calcula cuántas pizzas se vendieron en total y cuántas órdenes únicas hubo,
// luego divide ambos valores para obtener el promedio de pizzas por orden.

char* apo(int* size, Order* orders) {
    // Verificación inicial para evitar errores en datos
    if (!orders || *size <= 0) {
        return strdup("No hay datos disponibles.");
    }

    int total_pizzas = 0;
    int total_ordenes = 0;

    // Recorremos todas las órdenes para contar pizzas y órdenes únicas
    for (int i = 0; i < *size; i++) {
        total_pizzas += orders[i].quantity;  // Sumar todas las cantidades de pizzas

        // Contar órdenes únicas: asumimos que están ordenadas por order_id
        // y que cada cambio en order_id representa una nueva orden
        if (i == 0 || orders[i].order_id != orders[i - 1].order_id) {
            total_ordenes++;
        }
    }

    // Calcular promedio como número decimal
    double promedio = (double)total_pizzas / total_ordenes;

    // Reservamos espacio para mostrar el mensaje
    char* resultado = (char*)malloc(50 * sizeof(char));
    if (!resultado) {
        return strdup("Error de memoria.");
    }

    // Escribimos el resultado con formato
    snprintf(resultado, 50, "Promedio de pizzas por orden: %.2f", promedio);

    return resultado;
}


// Promedio de pizzas por día
// Esta métrica calcula cuántas pizzas se vendieron en total y cuántos días únicos hubo.
// Luego divide ambos para obtener un promedio de pizzas vendidas por día.

char* apd(int* size, Order* orders) {
    // Validación básica para evitar errores en datos nulos o vacíos
    if (!orders || *size <= 0) {
        return strdup("No hay datos disponibles.");
    }

    int num_fechas = 0;

    // Se llama a la función auxiliar que agrupa todas las fechas únicas encontradas en las órdenes
    // El resultado se almacena en un arreglo de structs 'FechaAgrupada'
    FechaAgrupada* fechas = agrupar_fechas_unicas(orders, *size, &num_fechas);

    if (!fechas || num_fechas == 0) {
        return strdup("Error al agrupar fechas.");  // Mensaje si no se agrupan fechas
    }

    int total_pizzas = 0;

    // Se suma la cantidad total de pizzas vendidas a lo largo de todas las órdenes
    for (int i = 0; i < *size; i++) {
        total_pizzas += orders[i].quantity;
    }

    // Promedio de pizzas vendidas por día: total dividido por cantidad de fechas únicas
    double promedio = (double)total_pizzas / num_fechas;

    // Reserva dinámica de memoria para el resultado
    char* resultado = (char*)malloc(50 * sizeof(char));
    if (!resultado) {
        free(fechas);  // Siempre liberar memoria en caso de error
        return strdup("Error de memoria.");
    }

    // Se formatea el resultado como string
    snprintf(resultado, 50, "Promedio de pizzas por día: %.2f", promedio);

    // Se libera la memoria asignada al arreglo de fechas únicas
    free(fechas);

    return resultado;
}


// Metrica propuesta para la separacion de ingredientes
// Utiliza un arreglo para contar la cantidad de veces que aparece cada ingrediente.
// Cuenta la cantidad de veces que aparece cada ingrediente y devuelve el más vendido.
char* ims(int* size, Order* orders) {
    // Validación inicial de entrada
    if (*size == 0 || orders == NULL) return strdup("Ingrediente más vendido: Sin datos");

    // Estructura local para almacenar nombre y conteo de cada ingrediente
    typedef struct {
        char nombre[64];
        int cantidad;
    } Ingrediente;

    // Arreglo dinámico para contar ingredientes, asumimos inicialmente 100 ingredientes distintos
    Ingrediente* conteos = malloc(sizeof(Ingrediente) * 100);
    int num_ingredientes = 0;

    // Recorremos todas las órdenes
    for (int i = 0; i < *size; i++) {
        // Copiamos la cadena de ingredientes porque strtok modifica el string original
        char* ingredientes = strdup(orders[i].pizza_ingredients);
        char* token = strtok(ingredientes, ",");  // Separar por comas

        // Procesar cada ingrediente individualmente
        while (token != NULL) {
            // Quitar espacios en blanco al inicio
            while (*token == ' ') token++;

            // Quitar espacios en blanco al final
            char* end = token + strlen(token) - 1;
            while (end > token && *end == ' ') *end-- = '\0';

            // Buscar si el ingrediente ya fue contado
            int encontrado = 0;
            for (int j = 0; j < num_ingredientes; j++) {
                if (strcmp(conteos[j].nombre, token) == 0) {
                    conteos[j].cantidad++;  // Incrementamos su conteo
                    encontrado = 1;
                    break;
                }
            }

            // Si no estaba, agregarlo al arreglo
            if (!encontrado) {
                strncpy(conteos[num_ingredientes].nombre, token, sizeof(conteos[num_ingredientes].nombre) - 1);
                conteos[num_ingredientes].nombre[sizeof(conteos[num_ingredientes].nombre) - 1] = '\0';
                conteos[num_ingredientes].cantidad = 1;
                num_ingredientes++;
            }

            token = strtok(NULL, ",");  // Siguiente ingrediente
        }

        free(ingredientes);  // Liberamos memoria de la copia
    }

    // Encontrar el ingrediente más frecuente
    int max_cantidad = 0;
    char* ingrediente_mas_vendido = malloc(64);  // Para almacenar temporalmente el nombre
    strcpy(ingrediente_mas_vendido, "Sin datos");

    for (int i = 0; i < num_ingredientes; i++) {
        if (conteos[i].cantidad > max_cantidad) {
            max_cantidad = conteos[i].cantidad;
            strncpy(ingrediente_mas_vendido, conteos[i].nombre, 64);
        }
    }

    // Preparar string de salida con el resultado
    char* resultado = malloc(128);
    snprintf(resultado, 128, "Ingrediente mas vendido: %s con %d ventas", ingrediente_mas_vendido, max_cantidad);

    // Liberar memoria usada
    free(conteos);
    free(ingrediente_mas_vendido);

    return resultado;
}

//Métrica pizzas vendidas por categoría
// Agrupa las órdenes por categoría de pizza y calcula la cantidad total vendida por cada categoría.
// Devuelve un string con las categorías y sus cantidades correspondientes.

typedef struct {
    char categoria[32];
    int cantidad;
} CategoriaVentas;

char* hp(int* size, Order* orders) {
    if (!orders || *size <= 0) {
        return strdup("No hay datos disponibles."); //Verificamos que el arreglo de órdenes no sea nulo o negativo
    }

    CategoriaVentas categorias[50]; //Creamos un arreglo para almacenar categorias y sus cantidades(en este caso son
    //solo dos, pero sí tuviéramos más se registrarian
    int numCategorias = 0;

    for (int i = 0; i < *size; i++) {
        Order order = orders[i];
        char* categoria = order.pizza_category;


        int found = 0;
        for (int k = 0; k < numCategorias; k++) {
            if (strcmp(categorias[k].categoria, categoria) == 0) {
                categorias[k].cantidad += order.quantity;
                found = 1;//Si la categoria ya esta registrada se suma al conteo de esa categoria
                break;
            }
        }


        if (!found) {
            strcpy(categorias[numCategorias].categoria, categoria);
            categorias[numCategorias].cantidad = order.quantity;
            numCategorias++; //Si la categoria no se encuentra previamente registrada se registra y se le suma la orden
        }
    }
    char* resultado = (char*)malloc(1024 * sizeof(char)); // Reservamos memoria suficiente(1024 bytes es suficiente)
    if (!resultado) {
        return strdup("Error de memoria.");
    }

    resultado[0] = '\0';
    for (int i = 0; i < numCategorias; i++) {
        char buffer[100];
        snprintf(buffer, sizeof(buffer), "%s: %d\n", categorias[i].categoria, categorias[i].cantidad);
        strcat(resultado, buffer);
    }//Se muestran las categorias y su cantidad

    return resultado;
}

// Métrica: Día con más pizzas vendidas (por cantidad)
// En esta función recorrimos todas las órdenes para agruparlas por fecha y contar cuántas pizzas se vendieron cada día.
// Lo que buscamos fue identificar la fecha con mayor cantidad de pizzas vendidas en total.

char* dmsp(int* size, Order* orders) {
    // Primero verificamos que el puntero a las órdenes sea válido
    if (!orders || *size <= 0) {
        return strdup("No hay datos disponibles.");
    }

    // Agrupamos las fechas únicas usando la función auxiliar agrupar_fechas_unicas()
    int num_fechas = 0;
    FechaAgrupada* fechas = agrupar_fechas_unicas(orders, *size, &num_fechas);
    if (!fechas || num_fechas == 0) {
        return strdup("Error al agrupar fechas.");
    }

    // Creamos un arreglo para contar la cantidad de pizzas vendidas por cada día
    int ventas_por_dia[num_fechas];
    memset(ventas_por_dia, 0, sizeof(ventas_por_dia)); // Inicializamos el arreglo en cero

    // Luego, por cada orden revisamos su fecha y sumamos su cantidad al total de ese día
    for (int i = 0; i < *size; i++) {
        for (int j = 0; j < num_fechas; j++) {
            if (strcmp(orders[i].order_date, fechas[j].fecha) == 0) {
                ventas_por_dia[j] += orders[i].quantity;
                break;
            }
        }
    }

    // Ahora buscamos el índice del día con la mayor cantidad de pizzas vendidas
    int max_ventas = ventas_por_dia[0];
    int max_index = 0;
    for (int i = 1; i < num_fechas; i++) {
        if (ventas_por_dia[i] > max_ventas) {
            max_ventas = ventas_por_dia[i];
            max_index = i;
        }
    }

    // Calculamos el tamaño exacto que necesitaremos para el mensaje final
    int largo = snprintf(NULL, 0, "Dia con mas pizzas vendidas: %s(%d pizzas)", 
                         fechas[max_index].fecha, max_ventas);

    // Reservamos la memoria y luego escribimos el mensaje
    char* resultado = (char*)malloc((largo + 1) * sizeof(char)); // +1 para '\0'
    if (!resultado) {
        free(fechas);
        return strdup("Error de memoria.");
    }

    // Guardamos el resultado con los datos calculados
    snprintf(resultado, largo + 1, "Dia con mas pizzas vendidas: %s(%d pizzas)", 
             fechas[max_index].fecha, max_ventas);

    // Liberamos la memoria que usamos para guardar las fechas agrupadas
    free(fechas);

    return resultado;
}



// Tabla de métricas


// En esta tabla estática declaramos todas las métricas disponibles en el programa.
// La estructura Metricas contiene el nombre de la métrica (como lo ingresa el usuario en consola)
// y un puntero a la función correspondiente que implementa la lógica de esa métrica.
//
// Esta organización nos pareció ideal porque nos permite mantener un listado ordenado y
// fácilmente extensible. Si más adelante agregamos nuevas métricas, solo tenemos que
// agregarlas aquí con su nombre y función respectiva.

static Metricas disponibles[] = {
    {"pms", pms},     // Pizza más vendida
    {"pls", pls},     // Pizza menos vendida
    {"dms", dms},     // Fecha con más ventas (dinero)
    {"dls", dls},     // Fecha con menos ventas (dinero)
    {"dmsp", dmsp},   // Fecha con más pizzas vendidas (cantidad)
    {"dlsp", dlsp},   // Fecha con menos pizzas vendidas (cantidad)
    {"apo", apo},     // Promedio de pizzas por orden
    {"apd", apd},     // Promedio de pizzas por día
    {"ims", ims},     // Ingrediente más vendido
    {"hp", hp}        // Histograma de pizzas por categoría
};


// Función de búsqueda de métrica


// Esta función recibe el nombre de la métrica ingresado por el usuario como string.
// Luego recorre la tabla de métricas (disponibles[]) y compara el nombre ingresado con cada uno.
// Si encuentra coincidencia, retorna el puntero a la función asociada.
// Si no encuentra ninguna coincidencia, retorna NULL.
//
// Esta lógica nos pareció adecuada porque evita el uso de múltiples condicionales
// (if o switch), manteniendo el código más limpio, compacto y mantenible.
// Además, es fácil de escalar si queremos agregar más métricas en el futuro.

Metrica obtener_metrica(const char* nombre) {
    int total = sizeof(disponibles) / sizeof(Metricas);  // Calculamos cuántas métricas hay

    for (int i = 0; i < total; i++) {
        if (strcmp(disponibles[i].name, nombre) == 0) {
            return disponibles[i].funcion;  // Retornamos el puntero a la función correspondiente
        }
    }

    return NULL;  // Si no se encuentra la métrica, se retorna NULL
}
