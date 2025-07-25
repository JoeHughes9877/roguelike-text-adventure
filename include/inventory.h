#ifndef INVENTORY_H
#define INVENTORY_H

#include "vector.h"

extern struct vector *inventory;

void add_to_inventory(char *input);
void print_inventory(void);
void check_if_in_inventory(void);
void remove_item_from_inventory(char *players_input);
struct vector *init_inventory(void);

#endif
