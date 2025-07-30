#ifndef INVENTORY_H
#define INVENTORY_H

#include "vector.h"
#include <stdbool.h>

extern struct vector *inventory;

void add_to_inventory(char *input);
void print_inventory();
void remove_item_from_inventory(char *players_input, bool is_dropping);
struct vector *init_inventory();
int check_if_in_inventory(char *item);

#endif
