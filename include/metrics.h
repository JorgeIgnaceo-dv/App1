#ifndef METRICS_H
#define METRICS_H

// Incluimos la definición del struct Order
#include "order.h"  
#include "helpers.h"
// Creamos el tipo de función general para métricas
typedef char* (*Metrica)(int*, Order*);

// Definimos el struct que representa una métrica
typedef struct {
    const char* name;
    Metrica funcion;
} Metricas;

// Declaración de la función que busca una métrica por su nombre
Metrica obtener_metrica(const char* nombre);

// Declaraciones de funciones métricas
char* pms(int* size, Order* orders);   // Pizza más vendida (Jorge)
char* pls(int* size, Order* orders);   // Pizza menos vendida (Carlos)
char* dms(int* size, Order* orders);   // Día con más ventas en dinero (Carlos)
char* dls(int* size, Order* orders);   // Día con menos ventas en dinero (Jorge)
char* dmsp(int* size, Order* orders);  // Día con más pizzas vendidas (Diego)
char* dlsp(int* size, Order* orders);  // Día con menos pizzas vendidas (Jorge)
char* apo(int* size, Order* orders);   // Promedio de pizzas por orden (Carlos)
char* apd(int* size, Order* orders);   // Promedio de pizzas por día (Diego)
char* ims(int* size, Order* orders);   // Ingrediente más vendido (Pendiente)
char* hp(int* size, Order* orders);    // Cantidad de pizzas por categoría vendidas (Diego)

#endif // METRICS_H
