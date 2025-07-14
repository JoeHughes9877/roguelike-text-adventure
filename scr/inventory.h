#ifndef INVENTORY_H
#define INVENTORY_H

extern char *inventory[8];

void add_to_inventory(char *input);
void print_inventory();
void check_if_in_inventory();
void remove_item();

#endif