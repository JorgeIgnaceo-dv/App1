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
//Métrica pizzas vendidas por categoría

// Definimos una estructura auxiliar para almacenar la cantidad de pizzas por categoría
typedef struct {
    char categoria[32]; // Tamaño basado en order.h
    int cantidad;
} CategoriaVentas;

// Función para obtener la cantidad de pizzas vendidas por categoría
char* hp(int* size, Order* orders) {
    if (!orders || *size <= 0) {
        return strdup("No hay datos disponibles.");
    }

    CategoriaVentas categorias[50]; // Asumimos un máximo de 50 categorías distintas
    int numCategorias = 0;

    for (int i = 0; i < *size; i++) {
        Order order = orders[i];
        char* categoria = order.pizza_category;

        // Buscar si la categoría ya está registrada
        int found = 0;
        for (int k = 0; k < numCategorias; k++) {
            if (strcmp(categorias[k].categoria, categoria) == 0) {
                categorias[k].cantidad += order.quantity;
                found = 1;
                break;
            }
        }

        // Si no la encontramos, la añadimos
        if (!found) {
            strcpy(categorias[numCategorias].categoria, categoria);
            categorias[numCategorias].cantidad = order.quantity;
            numCategorias++;
        }
    }

    // Construcción de la cadena de salida
    char* resultado = (char*)malloc(1024 * sizeof(char)); // Reservamos memoria suficiente
    if (!resultado) {
        return strdup("Error de memoria.");
    }

    resultado[0] = '\0';
    for (int i = 0; i < numCategorias; i++) {
        char buffer[100];
        snprintf(buffer, sizeof(buffer), "%s: %d\n", categorias[i].categoria, categorias[i].cantidad);
        strcat(resultado, buffer);
    }

    return resultado;
}

// =========================
// Tabla de métricas
// =========================


static Metricas disponibles[] = {
    {"pms", pms},
    // Puedes agregar las demás a medida que las implementes:
    // {"pls", pls},
    // {"dms", dms},
    {"dls", dls},
    // {"dmsp", dmsp},
    {"dlsp", dlsp},
    // {"apo", apo},
    // {"apd", apd},
    // {"ims", ims},
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
