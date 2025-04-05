#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "order.h"

// Función auxiliar para ver cuántas unidades se vendieron por cada pizza
void debug_pizzas(Order* orders, int n) {
    typedef struct {
        char nombre[128];
        int cantidad;
    } Conteo;

    Conteo* conteos = malloc(sizeof(Conteo) * n);
    int num_pizzas = 0;

    for (int i = 0; i < n; i++) {
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
            strncpy(conteos[num_pizzas].nombre, actual, sizeof(conteos[num_pizzas].nombre) - 1);
            conteos[num_pizzas].cantidad = cantidad;
            num_pizzas++;
        }
    }

    printf("\n[DEBUG] Conteo total de pizzas:\n");
    for (int i = 0; i < num_pizzas; i++) {
        printf(" - %s: %d unidades\n", conteos[i].nombre, conteos[i].cantidad);
    }

    free(conteos);
}
