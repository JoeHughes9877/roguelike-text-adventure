#include "inventory.h"
#include "header.h"
#include <stdio.h>
#include <string.h>

char *inventory[8];
int items_in_inventory = 0;

void print_inventory() {
  if (items_in_inventory == 0) {
    printf("You check your pockets... Yep, still nothing. Maybe try stealing "
           "something?\n");
    return;
  }

  printf("\n╔════════════════════════════════════╗\n");
  printf("║     Your questionable haul:        ║\n");
  printf("╚════════════════════════════════════╝\n");

  for (int i = 0; i < items_in_inventory; i++) {
    printf("  • %s\n", inventory[i]);
  }
}

void add_to_inventory(char *players_input) {
  if (items_in_inventory == 8) {
    printf("Hah! As if that’d fit — maybe ask a Mudcrab for advice?\n");
    return;
  }

  for (int i = 0; i < items.num_items_in_room; i++) {
    if (strstr(players_input, items.name[i])) {
      inventory[items_in_inventory] = items.name[i];
      printf("You carefully stow the %s into your pack.\n", items.name[i]);
      items_in_inventory += 1;
      return;
    }
  }
}

void check_if_in_inventory() {}

void remove_item() {}
