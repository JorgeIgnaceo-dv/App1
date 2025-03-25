#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

int main() {
    int n = 0;
    Order* orders = parse_csv("ventas.csv", &n);

    if (!orders) {
        printf("Error al leer el archivo CSV.\n");
        return 1;
    }

    printf("Se cargaron %d órdenes:\n\n", n);

    // Mostrar las primeras 3 como ejemplo
    for (int i = 0; i < n && i < 3; i++) {
        printf("Pedido #%d\n", i + 1);
        printf("  Pizza: %s\n", orders[i].pizza_name);
        printf("  Ingredientes: %s\n", orders[i].pizza_ingredients);
        printf("  Cantidad: %d\n", orders[i].quantity);
        printf("  Fecha: %s %s\n", orders[i].order_date, orders[i].order_time);
        printf("  Precio total: $%.2f\n", orders[i].total_price);
        printf("---------------------------\n");
    }

    free(orders);
    return 0;
}
// char* (metrica)(int *size, struct order *orders);