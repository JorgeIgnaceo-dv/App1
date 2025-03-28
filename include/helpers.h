#ifndef HELPERS_H
#define HELPERS_H

#include "order.h"

// Estructura básica que solo guarda fechas únicas agrupadas
typedef struct {
    char fecha[16];
} FechaAgrupada;

// Retorna arreglo con fechas únicas, sin repetirse
FechaAgrupada* agrupar_fechas_unicas(Order* orders, int size, int* num_fechas);

#endif
