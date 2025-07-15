#include "inventory.h"
#include "database.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct vector *inventory = NULL;

const int INVENTORY_SIZE = 8;

void print_inventory() {
  if (inventory->size == 0) {
    printf("You check your pockets... Yep, still nothing. Maybe try stealing "
           "something?\n");
    return;
  }

  printf("\n╔════════════════════════════════════╗\n");
  printf("║     Your questionable haul:        ║\n");
  printf("╚════════════════════════════════════╝\n");

  for (int i = 0; i < inventory->size; i++) {
    printf("  • %s\n", inventory->elements[i]);
  }
}

void add_to_inventory(char *players_input) {
  if (!inventory) {
    init_inventory();
  }

  if (inventory->size == inventory->capacity) {
    printf("Hah! As if that’d fit — maybe ask a Mudcrab for advice?\n");
    return;
  }

  for (int i = 0; i < items.num_items_in_room; i++) {
    if (strstr(players_input, items.name->elements[i]) != NULL) {
      inventory->elements[inventory->size] = strdup(items.name->elements[i]);

      printf("You carefully stow the %s into your pack.\n",
             items.name->elements[i]);
      inventory->size++;
      return;
    }
  }
}

void check_if_in_inventory() {}

void remove_item() {}

struct vector *init_inventory() {
  struct vector *inventory =
      malloc(sizeof(struct vector) + INVENTORY_SIZE * sizeof(char *));
  inventory->size = 0;
  inventory->capacity = 8;

  return inventory;
}