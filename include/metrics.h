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
char* pms(int* size, Order* orders);   // Pizza más vendida(Jorge)
char* pls(int* size, Order* orders);   // Pizza menos vendida(Carlos)
char* dms(int* size, Order* orders);   // Día con más ventas en dinero(Carlos)
char* dls(int* size, Order* orders);   // Día con menos ventas en dinero(Jorge)
char* dmsp(int* size, Order* orders);  // Día con más pizzas vendidas(Diego)
char* dlsp(int* size, Order* orders);  // Día con menos pizzas vendidas(Jorge)
char* apo(int* size, Order* orders);   // Promedio de pizzas por orden(Carlos)
char* apd(int* size, Order* orders);   // Promedio de pizzas por día(Diego)
char* ims(int* size, Order* orders);   // Ingrediente más vendido(Pendiente)
char* hp(int* size, Order* orders);    // Cantidad de pizzas por categoria vendidas(Diego)

#endif

