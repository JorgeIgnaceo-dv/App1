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
    fgets(line, MAX_LINE, file); // Saltarse encabezado

    int capacity = INITIAL_CAPACITY;
    Order* orders = malloc(sizeof(Order) * capacity);
    *num_orders = 0;

    while (fgets(line, MAX_LINE, file)) {
        if (*num_orders >= capacity) {
            capacity *= 2;
            orders = realloc(orders, sizeof(Order) * capacity);
        }

        Order* o = &orders[*num_orders];

        int campos_leidos = sscanf(
            line,
            "%d,%d,%63[^,],%d,%15[^,],%15[^,],%f,%f,%3[^,],%31[^,],\"%255[^\"]\",%127[^\n]",
            &o->pizza_id,
            &o->order_id,
            o->pizza_name_id,
            &o->quantity,
            o->order_date,
            o->order_time,
            &o->unit_price,
            &o->total_price,
            o->pizza_size,
            o->pizza_category,
            o->pizza_ingredients,
            o->pizza_name
        );

        if (campos_leidos == 12) {
            (*num_orders)++;
        } else {
            // Línea mal formada, puedes mostrarla para depuración:
            printf("Línea ignorada (formato inválido): %s", line);
        }
    }

    fclose(file);
    return orders;
}


