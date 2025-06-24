#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

#define MAX_LINE 1024
#define INITIAL_CAPACITY 1000

Order* parse_csv(const char* filename, int* num_orders) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error al abrir archivo");
        return NULL;
    }

    char line[MAX_LINE];
    fgets(line, MAX_LINE, file); // Saltar encabezado

    int capacity = INITIAL_CAPACITY;
    Order* orders = malloc(sizeof(Order) * capacity);
    if (!orders) {
        perror("No se pudo asignar memoria");
        fclose(file);
        return NULL;
    }

    *num_orders = 0;

    while (fgets(line, MAX_LINE, file)) {
        if (*num_orders >= capacity) {
            capacity *= 2;
            Order* temp = realloc(orders, sizeof(Order) * capacity);
            if (!temp) {
                perror("Error al redimensionar memoria");
                free(orders);
                fclose(file);
                return NULL;
            }
            orders = temp;
        }

        Order* o = &orders[*num_orders];

        // Punteros auxiliares
        char ingredientes[256], nombre[128];

        // Corregido: leer decimales como float
        float pizza_id_f, order_id_f, quantity_f;

        int campos_leidos = sscanf(
            line,
            "%f,%f,%63[^,],%f,%15[^,],%15[^,],%f,%f,%3[^,],%31[^,],",
            &pizza_id_f,
            &order_id_f,
            o->pizza_name_id,
            &quantity_f,
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

        o->pizza_id = (int)pizza_id_f;
        o->order_id = (int)order_id_f;
        o->quantity = (int)quantity_f;

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
        ingredientes[sizeof(ingredientes) - 1] = '\0';

        // Luego avanzar al nombre de la pizza (después de la segunda comilla + una coma)
        char* after = end + 2;
        strncpy(nombre, after, sizeof(nombre) - 1);
        nombre[sizeof(nombre) - 1] = '\0';

        // Limpiar posibles saltos de línea
        nombre[strcspn(nombre, "\r\n")] = '\0';

        // Guardar en el struct
        strncpy(o->pizza_ingredients, ingredientes, sizeof(o->pizza_ingredients) - 1);
        o->pizza_ingredients[sizeof(o->pizza_ingredients) - 1] = '\0';

        strncpy(o->pizza_name, nombre, sizeof(o->pizza_name) - 1);
        o->pizza_name[sizeof(o->pizza_name) - 1] = '\0';

        (*num_orders)++;
    }

    fclose(file);
    return orders;
}
