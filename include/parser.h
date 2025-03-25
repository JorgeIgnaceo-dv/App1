// A continuación, definimos el archivo que servirá para parsear el CSV.

#ifndef PARSER_H
#define PARSER_H

#include "order.h"

Order* parse_csv(const char* filename, int* num_orders);

#endif