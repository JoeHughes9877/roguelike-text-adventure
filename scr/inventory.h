#ifndef INVENTORY_H
#define INVENTORY_H

#include "vector.h"

extern struct vector *inventory;

void add_to_inventory(char *input);
void print_inventory();
void check_if_in_inventory();
void remove_item();
struct vector *init_inventory();

#endif