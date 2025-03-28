#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "metrics.h"
#include "debug.h"
#include "helpers.h"

// Mostrar instrucciones cuando sea necesario
void mostrar_instrucciones() {
    printf("============================================\n");
    printf("   Bienvenido al sistema de análisis TICS\n");
    printf("============================================\n");
    printf("Instrucciones:\n");
    printf("  Uso: ./app1 archivo.csv metrica1 metrica2 ...\n\n");
    printf("Métricas disponibles:\n");
    printf("  1. pms   -> Pizza más vendida\n");
    printf("  2. pls   -> Pizza menos vendida\n");
    printf("  3. dms   -> Fecha con más ventas (dinero)\n");
    printf("  4. dls   -> Fecha con menos ventas (dinero)\n");
    printf("  5. dmsp  -> Fecha con más pizzas vendidas (cantidad)\n");
    printf("  6. dlsp  -> Fecha con menos pizzas vendidas (cantidad)\n");
    printf("  7. apo   -> Promedio de pizzas por orden\n");
    printf("  8. apd   -> Promedio de pizzas por día\n");
    printf("  9. ims   -> Ingrediente más vendido\n");
    printf(" 10. hp    -> Cantidad de pizzas por categoría\n");
    printf("--------------------------------------------\n");
    printf("Por favor ingresar las métricas luego del archivo.\n\n");
}

// Verifica si hay al menos una métrica válida
int hay_metricas_validas(int cant, char** metricas, int* n, Order* orders) {
    //con esto evitamos el Warning de una supuesta variable no usada, ya que esta variable será necesaria dentro de esta función para poder usarla más adelante.
    (void)n;
    (void)orders;

    for (int i = 0; i < cant; i++) {
        if (obtener_metrica(metricas[i]) != NULL) {
            return 1;
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {
    char archivo[256] = "";
    Order* orders = NULL;
    int n = 0;
    char* metricas[20];
    int num_metricas = 0;
    int archivo_ok = 0;
    int metricas_ok = 0;

    // -------------------------------
    // 1. Intentar cargar desde argumentos
    // -------------------------------
    if (argc >= 2) {
        strncpy(archivo, argv[1], sizeof(archivo));
        orders = parse_csv(archivo, &n);
        archivo_ok = (orders && n > 0);

        if (!archivo_ok) {
            printf("⚠️  Error al cargar el archivo '%s'.\n", archivo);
        }
    }

    if (argc >= 3) {
        for (int i = 2; i < argc && num_metricas < 20; i++) {
            metricas[num_metricas++] = argv[i];
        }
        if (archivo_ok) {
            metricas_ok = hay_metricas_validas(num_metricas, metricas, &n, orders);
        }
    }

    // -------------------------------
    // 2. Si no hay archivo válido, pedirlo
    // -------------------------------
    if (!archivo_ok) {
        mostrar_instrucciones();

        do {
            printf("Ingrese el nombre del archivo CSV: ");
            fgets(archivo, sizeof(archivo), stdin);
            archivo[strcspn(archivo, "\n")] = 0;
            orders = parse_csv(archivo, &n);
            archivo_ok = (orders && n > 0);
            if (!archivo_ok) printf("⚠️  Archivo no válido. Intente de nuevo.\n");
        } while (!archivo_ok);
    }

    printf("\n✅ Archivo cargado con %d órdenes.\n", n);

    // -------------------------------
    // 3. Si no hay métricas válidas, pedirlas
    // -------------------------------
    if (!metricas_ok) {
        mostrar_instrucciones();

        char linea[512];
        do {
            printf("Ingrese métricas separadas por espacio: ");
            fgets(linea, sizeof(linea), stdin);
            linea[strcspn(linea, "\n")] = 0;

            num_metricas = 0;
            char* token = strtok(linea, " ");
            while (token && num_metricas < 20) {
                metricas[num_metricas++] = token;
                token = strtok(NULL, " ");
            }

            metricas_ok = hay_metricas_validas(num_metricas, metricas, &n, orders);
            if (!metricas_ok) {
                printf("⚠️  Ninguna métrica válida. Intente de nuevo.\n");
            }
        } while (!metricas_ok);
    }

    // -------------------------------
    // 4. Ejecutar métricas válidas
    // -------------------------------
    printf("\n--- Resultados ---\n");
    for (int i = 0; i < num_metricas; i++) {
        Metrica m = obtener_metrica(metricas[i]);
        if (m) {
            char* resultado = m(&n, orders);
            printf("%s\n", resultado);
            free(resultado);
        } else {
            printf("Métrica '%s' no reconocida (omitida).\n", metricas[i]);
        }
    }

    free(orders);
    return 0;
}
