#include "database.h"
#include "inventory.h"
#include "room.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

void opening();
void game_loop();
void delay(int number_of_seconds);

char *lower_player_input(char *input);

int main() {
  inventory = init_inventory();
  items.name = init_items();
  items.description = init_items();
  items.type = init_items();

  set_start_room();
  opening();

  game_loop();
}
void opening() {
  printf("====================================================================="
         "==========\n");
  printf("                        The Elder Scrolls: Shadows of Tamriel\n");
  printf("====================================================================="
         "==========\n\n");

  printf("  \"When the Dragonfires dim and the blood of kings runs cold, "
         "darkness stirs...\"\n\n");

  printf("  You awaken in a damp stone cell beneath the Imperial City.\n");
  printf("  Your head throbs from a blow you don’t remember receiving.\n");
  printf("  Then — a thunderous explosion shakes the ground.\n");
  printf("  Dust rains from the ceiling. Somewhere nearby, a wall has "
         "collapsed to your north.\n");
  printf("  Screams echo down the corridor... and your cell door west of you "
         "creaks "
         "open.\n\n");
  printf("  Freedom — unexpected and unearned — lies before you.\n");

  printf("---------------------------------------------------------------------"
         "----------\n");
  printf("\nPress Enter to continue...");
  getchar(); // Waits for the user to press Enter

  printf("\nThe threads of fate twist around you...");
  char *name =
      get_string("But before your journey begins — tell me: who are you? ");

  printf("With the taste of freedom fresh on your lips, what path will you "
         "take? %s",
         name);
}

void game_loop() {
  while (1) {
    char *player_input = get_string("What do you do? ");

    player_input = lower_player_input(player_input);

    if (strstr(player_input, "go north") != NULL) {
      generate_room();
      generate_exits_in_room("north");
    } else if (strstr(player_input, "go east") != NULL) {
      generate_room();
      generate_exits_in_room("east");
    } else if (strstr(player_input, "go south") != NULL) {
      generate_room();
      generate_exits_in_room("south");
    } else if (strstr(player_input, "go west") != NULL) {
      generate_room();
      generate_exits_in_room("west");
    } else if (strstr(player_input, "look around") != NULL) {
      look_around_room();
    } else if (strstr(player_input, "inventory") != NULL) {
      print_inventory();
    } else if (strstr(player_input, "take") != NULL) {
      add_to_inventory(player_input);
    } else if (strstr(player_input, "drop") != NULL) {
      remove_item_from_inventory(player_input);
    } else {
      printf("Even the gods seem puzzled by that request.\n");
    }
  }
}