#include <stdlib.h>
#include <string.h>
#include "helpers.h"

FechaAgrupada* agrupar_fechas_unicas(Order* orders, int size, int* num_fechas) {
    FechaAgrupada* fechas = malloc(sizeof(FechaAgrupada) * size);
    *num_fechas = 0;

    for (int i = 0; i < size; i++) {
        char* actual = orders[i].order_date;
        int encontrada = 0;

        for (int j = 0; j < *num_fechas; j++) {
            if (strcmp(fechas[j].fecha, actual) == 0) {
                encontrada = 1;
                break;
            }
        }

        if (!encontrada) {
            strncpy(fechas[*num_fechas].fecha, actual, sizeof(fechas[*num_fechas].fecha) - 1);
            (*num_fechas)++;
        }
    }

    return fechas;
}
