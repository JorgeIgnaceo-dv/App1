//A continuación, creamos el struct Order. Este Struct será llenando con los distintos datos del csv. 
#ifndef ORDER_H
#define ORDER_H
// el contenido del struct Order serían los distintos miembros, los cuales son las variables del archivo csv.
typedef struct {
    int pizza_id;
    int order_id;
    char pizza_name_id[64];
    int quantity;
    char order_date[16];
    char order_time[16];
    float unit_price;
    float total_price;
    char pizza_size[4];
    char pizza_category[32];
    char pizza_ingredients[256];
    char pizza_name[128];
} Order;

#endif