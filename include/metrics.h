#ifndef METRICS_H
#define METRICS_H
// Incluimos la biblioteca order.h ya que las metricas necesitan recibir 
#include "order.h"  

//Creamos el tipo de función general para métrica, la cual recibe: (tamaño, órdenes) y devuelve un string
typedef char* (*Metrica)(int*, Order*);

// Definimos un struct que representa cada métrica
typedef struct {
    const char* name;
    Metrica funcion;
} Metricas;

// Declaraciones de funciones métricas
char* pms(int* size, Order* orders);   // Pizza más vendida
char* pls(int* size, Order* orders);   // Pizza menos vendida
char* dms(int* size, Order* orders);   // Día con más ventas en dinero
char* dls(int* size, Order* orders);   // Día con menos ventas en dinero
char* dmsp(int* size, Order* orders);  // Día con más pizzas vendidas
char* dlsp(int* size, Order* orders);  // Día con menos pizzas vendidas
char* apo(int* size, Order* orders);   // Promedio de pizzas por orden
char* apd(int* size, Order* orders);   // Promedio de pizzas por día
char* ims(int* size, Order* orders);   // Ingrediente más vendido
char* hp(int* size, Order* orders);    // Histograma por categoría

#endif

