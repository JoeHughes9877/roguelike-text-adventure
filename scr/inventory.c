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

  printf("\n╔════════════════════════════════════╗\n");
  printf("║     Your questionable haul:        ║\n");
  printf("╚════════════════════════════════════╝\n");

  for (int i = 0; i < inventory->size; i++) {
    printf("  • %s\n", inventory->elements[i]);
  }
}

void add_to_inventory(char *players_input) {
  printf("[DEBUG] Input: '%s'\n", players_input);

  if (!inventory) {
    printf("[DEBUG] Initializing inventory\n");
    inventory = init_inventory();
  }

  if (inventory->size == inventory->capacity) {
    printf("[DEBUG] Inventory full (size: %d)\n", inventory->size);
    printf("Hah! As if that’d fit — maybe ask a Mudcrab for advice?\n");
    return;
  }

  for (int i = 0; i < items.num_items_in_room; i++) {
    printf("[DEBUG] Checking room item %d: '%s'\n", i, items.name->elements[i]);
    if (strstr(players_input, items.name->elements[i]) != NULL) {
      printf("[DEBUG] Found '%s' in room at index %d\n", players_input, i);

      remove_item_from_room(items.name->elements[i]);
      inventory->elements[inventory->size] = strdup(items.name->elements[i]);
      inventory->size++;

      printf("[DEBUG] Added '%s' to inventory (size now %d)\n",
             items.name->elements[i], inventory->size);
      printf("You carefully stow the %s into your pack.\n",
             items.name->elements[i]);
      return;
    }
  }

  printf("[DEBUG] '%s' not found in the room\n", players_input);
  printf("You don't see a %s here.\n", players_input);
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
  for (int i = 0; i < items.num_items_in_room; i++) {
    if (strstr(players_input, items.name->elements[i]) != NULL) {
      printf("You cast away '%s', hopeful it will one day find purpose in "
             "another’s hands.\n",
             items.name->elements[i]);
      delete_by_value(inventory, items.name->elements[i]);
      return;
    }
  }
}

struct vector *init_inventory() {
  struct vector *inventory =
      malloc(sizeof(struct vector) + INVENTORY_SIZE * sizeof(char *));
  inventory->size = 0;
  inventory->capacity = 8;

  return inventory;
}