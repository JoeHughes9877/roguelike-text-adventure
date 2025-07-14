#include "inventory.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

char *inventory[8];
int items_in_inventory = 3;

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
  players_input = find_item_in_text(players_input);
}

void check_if_in_inventory() {}

void remove_item() {}

char *find_item_in_text(char *players_input) {
  while (1) {
    char *token = strtok(players_input, " ");

    if (strcmp(token, "take")) {
      char *token =
          strtok(NULL, " "); // Null allows it to carry on from the previous
      printf("%s", token);
      return token;
    }
    if (token == NULL) {
      return ("cannot find item.");
    }
  }
}
