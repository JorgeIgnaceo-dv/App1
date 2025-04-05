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

// Pizza más vendida
// Recorre las órdenes y agrupa las pizzas por nombre, sumando las cantidades vendidas.
// Identifica las pizzas con la mayor cantidad vendida y devuelve un string con el resultado.
char* pms(int* size, Order* orders) {
    if (*size == 0 || orders == NULL) return strdup("Pizza más vendida: Sin datos");

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

    int max_cantidad = 0;
    for (int i = 0; i < num_pizzas; i++) {
        if (conteos[i].cantidad > max_cantidad) {
            max_cantidad = conteos[i].cantidad;
        }
    }

    // Crear string con las pizzas más vendidas
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
// Misma logica que en pms
// Identifica las pizzas con la menor cantidad y devuelve un string con el resultado.

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
    int min_cantidad = __INT_MAX__; // Inicializar con un valor alto
    // Averiguar que significa  INT MAX
    for (int i = 0; i < num_pizzas; i++) {
        if (conteos[i].cantidad < min_cantidad) {
            min_cantidad = conteos[i].cantidad;
        }
    }

    // Crear string con las pizzas menos vendidas
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
// Agrupa las órdenes por fecha y calcula el total de ventas en dinero para cada fecha.
// Devuelve la fecha con el día más vendido y el monto.
char* dms(int* size, Order* orders) {
    if (*size == 0 || orders == NULL) return strdup("Sin datos");

    int num_fechas = 0;
    FechaAgrupada* fechas = agrupar_fechas_unicas(orders, *size, &num_fechas);

    if (num_fechas == 0) {
        free(fechas);
        return strdup("Sin fechas agrupadas.");
    }

    float max_total = 0.0; // Inicializar con el valor más bajo posible
    char fecha_max[16] = "";

    for (int i = 0; i < num_fechas; i++) {
        float suma = 0.0;
        for (int j = 0; j < *size; j++) {
            if (strcmp(fechas[i].fecha, orders[j].order_date) == 0) {
                suma += orders[j].total_price;
            }
        }

        if (suma > max_total) {
            max_total = suma;
            strncpy(fecha_max, fechas[i].fecha, sizeof(fecha_max) - 1);
        }
    }

    char* resultado = malloc(128);
    snprintf(resultado, 128, "La fecha con más ventas es: %s con $%.2f", fecha_max, max_total);

    free(fechas);
    return resultado;
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

// Fecha con menos ventas (cantidad)
// Agrupa las órdenes por fecha y calcula la cantidad total de pizzas vendidas por fecha.
// Devuelve la fecha con la menor cantidad de pizzas vendidas.

char* dlsp(int* size, Order* orders) {
    if (*size == 0 || orders == NULL) return strdup("Sin datos");

    int num_fechas = 0;
    FechaAgrupada* fechas = agrupar_fechas_unicas(orders, *size, &num_fechas);

    if (num_fechas == 0) {
        free(fechas);
        return strdup("Sin fechas agrupadas.");
    }

    int min_cantidad = __INT_MAX__;
    char fecha_min[16] = "";

    for (int i = 0; i < num_fechas; i++) {
        int suma = 0;
        for (int j = 0; j < *size; j++) {
            if (strcmp(fechas[i].fecha, orders[j].order_date) == 0) {
                suma += orders[j].quantity;
            }
        }

        if (suma < min_cantidad) {
            min_cantidad = suma;
            strncpy(fecha_min, fechas[i].fecha, sizeof(fecha_min) - 1);
        }
    }

    char* resultado = malloc(128);
    snprintf(resultado, 128, "La fecha con menos pizzas vendidas es: %s con %d unidades", fecha_min, min_cantidad);

    free(fechas);
    return resultado;
}

// Promedio de pizzas por orden
// Calcula el promedio de pizzas vendidas por cada orden única.
// Devuelve un string con el promedio calculado.

char* apo(int* size, Order* orders) {
    if (!orders || *size <= 0) {
        return strdup("No hay datos disponibles.");
    }

    int total_pizzas = 0;
    int total_ordenes = 0;

    // Contar el total de pizzas y el número de órdenes únicas
    for (int i = 0; i < *size; i++) {
        total_pizzas += orders[i].quantity;

        // Contar órdenes únicas (asumiendo que cada `order_id` es único por orden)
        if (i == 0 || orders[i].order_id != orders[i - 1].order_id) {
            total_ordenes++;
        }
    }

    // Calcular el promedio
    double promedio = (double)total_pizzas / total_ordenes;

    // Crear el resultado
    char* resultado = (char*)malloc(50 * sizeof(char));
    if (!resultado) {
        return strdup("Error de memoria.");
    }

    snprintf(resultado, 50, "Promedio de pizzas por orden: %.2f", promedio);

    return resultado;
}

//Metrica de promedio de pizzas por dia
// Agrupa las órdenes por fecha y calcula el promedio de pizzas vendidas por día.
// Devuelve un string con el promedio calculado.

char* apd(int* size, Order* orders) {
    if (!orders || *size <= 0) {
        return strdup("No hay datos disponibles.");//Si el arreglo de ordenes es igual o menor a 0 imprime un mensaje
    }
    int num_fechas = 0;
    FechaAgrupada* fechas = agrupar_fechas_unicas(orders, *size, &num_fechas);
    if (!fechas || num_fechas == 0) {
        return strdup("Error al agrupar fechas.");//Usando helpers.c se encuentran las fechas unicas
    }
    int total_pizzas = 0;
    for (int i = 0; i < *size; i++) {
        total_pizzas += orders[i].quantity; //Se suman todas las pizzas vendidas
    }
    double promedio = (double)total_pizzas / num_fechas; //Se calcula el promedio dividiendo la cantidad por los dias unicos

    char* resultado = (char*)malloc(50 * sizeof(char));
    if (!resultado) {
        free(fechas);
        return strdup("Error de memoria.");
    }

    snprintf(resultado, 50, "Promedio de pizzas por día: %.2f", promedio); //Se imprime el promedio calculado

    // Limpiar la basura(liberar memoria)
    free(fechas);

    return resultado;
}

// Metrica propuesta para la separacion de ingredientes
// Utiliza un arreglo para contar la cantidad de veces que aparece cada ingrediente.
// Cuenta la cantidad de veces que aparece cada ingrediente y devuelve el más vendido.
char* ims(int* size, Order* orders) {
    if (*size == 0 || orders == NULL) return strdup("Ingrediente más vendido: Sin datos");

    // Estructura para almacenar el conteo de ingredientes
    typedef struct {
        char nombre[64];
        int cantidad;
    } Ingrediente;

    Ingrediente* conteos = malloc(sizeof(Ingrediente) * 100); // Capacidad inicial para 100 ingredientes
    int num_ingredientes = 0;

    for (int i = 0; i < *size; i++) {
        char* ingredientes = strdup(orders[i].pizza_ingredients); // Copiar los ingredientes de la orden
        char* token = strtok(ingredientes, ","); // Separar por comas

        while (token != NULL) {
            // Eliminar espacios en blanco al inicio y al final
            while (*token == ' ') token++;
            char* end = token + strlen(token) - 1;
            while (end > token && *end == ' ') *end-- = '\0';

            // Buscar si el ingrediente ya está en el conteo
            int encontrado = 0;
            for (int j = 0; j < num_ingredientes; j++) {
                if (strcmp(conteos[j].nombre, token) == 0) {
                    conteos[j].cantidad++;
                    encontrado = 1;
                    break;
                }
            }

            // Si no está, agregarlo al conteo
            if (!encontrado) {
                strncpy(conteos[num_ingredientes].nombre, token, sizeof(conteos[num_ingredientes].nombre) - 1);
                conteos[num_ingredientes].nombre[sizeof(conteos[num_ingredientes].nombre) - 1] = '\0';
                conteos[num_ingredientes].cantidad = 1;
                num_ingredientes++;
            }

            token = strtok(NULL, ","); // Siguiente ingrediente
        }

        free(ingredientes); // Liberar memoria de la copia
    }

    // Encontrar el ingrediente más vendido
    int max_cantidad = 0;
    char* ingrediente_mas_vendido = malloc(64);
    strcpy(ingrediente_mas_vendido, "Sin datos");

    for (int i = 0; i < num_ingredientes; i++) {
        if (conteos[i].cantidad > max_cantidad) {
            max_cantidad = conteos[i].cantidad;
            strncpy(ingrediente_mas_vendido, conteos[i].nombre, 64);
        }
    }

    // Crear el resultado
    char* resultado = malloc(128);
    snprintf(resultado, 128, "Ingrediente mas vendido: %s con %d ventas", ingrediente_mas_vendido, max_cantidad);

    // Liberar memoria
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
//Metrica para mostrar el dia con menos pizzas vendidas
char* dmsp(int* size, Order* orders) {
    if (!orders || *size <= 0) {
        return strdup("No hay datos disponibles.");
    }

    // Obtener las fechas únicas
    int num_fechas = 0;
    FechaAgrupada* fechas = agrupar_fechas_unicas(orders, *size, &num_fechas);
    if (!fechas || num_fechas == 0) {
        return strdup("Error al agrupar fechas.");
    }

    // Crear un array para contar las pizzas vendidas por día
    int ventas_por_dia[num_fechas];
    memset(ventas_por_dia, 0, sizeof(ventas_por_dia));

    // Contar cuántas pizzas se vendieron cada día
    for (int i = 0; i < *size; i++) {
        for (int j = 0; j < num_fechas; j++) {
            if (strcmp(orders[i].order_date, fechas[j].fecha) == 0) {
                ventas_por_dia[j] += orders[i].quantity;
                break;
            }
        }
    }

    // Encontrar el día con más pizzas vendidas
    int max_ventas = ventas_por_dia[0];
    int max_index = 0;
    for (int i = 1; i < num_fechas; i++) {
        if (ventas_por_dia[i] > max_ventas) {
            max_ventas = ventas_por_dia[i];
            max_index = i;
        }
    }

    // Calcular dinámicamente el tamaño necesario para el resultado
    int largo = snprintf(NULL, 0, "Dia con mas pizzas vendidas: %s(%d pizzas)", 
                         fechas[max_index].fecha, max_ventas);
    char* resultado = (char*)malloc((largo + 1) * sizeof(char)); // +1 para '\0'
    if (!resultado) {
        free(fechas);
        return strdup("Error de memoria.");
    }

    // Escribir el resultado final
    snprintf(resultado, largo + 1, "Dia con mas pizzas vendidas: %s(%d pizzas)", 
             fechas[max_index].fecha, max_ventas);

    // Liberar memoria de fechas únicas
    free(fechas);

    return resultado;
}


// =========================
// Tabla de métricas
// =========================


static Metricas disponibles[] = {
    {"pms", pms},
    // Puedes agregar las demás a medida que las implementes:
    {"pls", pls},
    {"dms", dms},
    {"dls", dls},
    {"dmsp", dmsp},
    {"dlsp", dlsp},
    {"apo", apo},
    {"apd", apd},
    {"ims", ims},
    {"hp", hp},
};

// =========================
// Función de búsqueda de métrica
// =========================

Metrica obtener_metrica(const char* nombre) {
    int total = sizeof(disponibles) / sizeof(Metricas);
    for (int i = 0; i < total; i++) {
        if (strcmp(disponibles[i].name, nombre) == 0) {
            return disponibles[i].funcion;
        }
    }
    return NULL;
}
