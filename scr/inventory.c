#include "inventory.h"
#include "database.h"
#include "room.h"
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

  printf("╔════════════════════════════════════╗\n");
  printf("║     Your questionable haul:        ║\n");
  printf("╚════════════════════════════════════╝\n");

  for (int i = 0; i < inventory->size; i++) {
    printf("  • %s\n", inventory->elements[i]);
  }
}

void add_to_inventory(char *players_input) {
  // Check if inventory is full
  if (inventory->size == inventory->capacity) {
    printf("Hah! As if that’d fit — maybe ask a Mudcrab for advice?\n");
    return;
  }

  // Iterate through the items in the room
  for (int i = 0; i < items.num_items_in_room; i++) {

    // Check if player's input matches the current item
    if (strstr(players_input, items.name->elements[i]) != NULL) {
      inventory->elements[inventory->size] =
          malloc(strlen(items.name->elements[i]) + 1);

      snprintf(inventory->elements[inventory->size],
               strlen(items.name->elements[i]) + 1, "%s",
               items.name->elements[i]);

      printf("You carefully stow the %s into your pack.\n",
             items.name->elements[i]);

      inventory->size++;
      remove_item_from_room(items.name->elements[i]);
      return;
    }
  }

  printf("You don't see that item here.\n");
}

void remove_item(char *players_input) {
  if (!inventory) {
    inventory = init_inventory();
  }
  // if empty
  if (inventory->size == 0) {
    printf(
        "Even Sheogorath couldn’t conjure an item from *this* sorry state.\n");
    return;
  }

  for (int i = 0; i < inventory->size; i++) {
    if (strstr(players_input, inventory->elements[i]) != NULL) {
      printf("You cast away '%s', hopeful it will one day find purpose in "
             "another’s hands.\n",
             inventory->elements[i]);

      delete_by_index(inventory, i);
      return;
    }
  }
}

struct vector *init_inventory() {
  struct vector *inventory = malloc(sizeof(struct vector));
  inventory->size = 0;
  inventory->capacity = 8;
  inventory->elements = malloc(inventory->capacity * sizeof(char *));

  return inventory;
}