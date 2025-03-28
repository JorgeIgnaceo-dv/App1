#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

#define MAX_LINE 1024
#define INITIAL_CAPACITY 1000

Order* parse_csv(const char* filename, int* num_orders) {
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;

    char line[MAX_LINE];
    fgets(line, MAX_LINE, file); // Saltar encabezado

    int capacity = INITIAL_CAPACITY;
    Order* orders = malloc(sizeof(Order) * capacity);
    *num_orders = 0;

    while (fgets(line, MAX_LINE, file)) {
        if (*num_orders >= capacity) {
            capacity *= 2;
            orders = realloc(orders, sizeof(Order) * capacity);
        }

        Order* o = &orders[*num_orders];

        // Punteros auxiliares
        char ingredientes[256], nombre[128];

        // Primero parseamos hasta pizza_category
        int campos_leidos = sscanf(
            line,
            "%d,%d,%63[^,],%d,%15[^,],%15[^,],%f,%f,%3[^,],%31[^,],",
            &o->pizza_id,
            &o->order_id,
            o->pizza_name_id,
            &o->quantity,
            o->order_date,
            o->order_time,
            &o->unit_price,
            &o->total_price,
            o->pizza_size,
            o->pizza_category
        );

        if (campos_leidos != 10) {
            printf("Línea ignorada (formato inválido): %s", line);
            continue;
        }

        // Buscar el campo entre comillas dobles para ingredientes
        char* start = strchr(line, '"');
        if (!start) {
            printf("Ingredientes no encontrados: %s", line);
            continue;
        }
        start++; // avanzar para ignorar la primera comilla

        char* end = strchr(start, '"');
        if (!end) {
            printf("Fin de ingredientes no encontrado: %s", line);
            continue;
        }

        size_t len = end - start;
        if (len >= sizeof(ingredientes)) len = sizeof(ingredientes) - 1;
        strncpy(ingredientes, start, len);
        ingredientes[len] = '\0';

        // Luego avanzar al nombre de la pizza (después de la segunda comilla + una coma)
        char* after = end + 2;
        strncpy(nombre, after, sizeof(nombre));
        nombre[sizeof(nombre) - 1] = '\0';

        // Guardar en el struct
        strncpy(o->pizza_ingredients, ingredientes, sizeof(o->pizza_ingredients));
        strncpy(o->pizza_name, nombre, sizeof(o->pizza_name));

        // Limpiar posibles saltos de línea
        o->pizza_name[strcspn(o->pizza_name, "\r\n")] = '\0';

        (*num_orders)++;
    }

    fclose(file);
    return orders;
}