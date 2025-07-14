#include "header.h"
#include "inventory.c"
#include <stdio.h>
#include <string.h>
#include <time.h>

void opening();
void game_loop();
void delay(int number_of_seconds);

int main() {
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

  delay(3);

  printf("With the taste of freedom fresh on your lips, what path will you "
         "take? ");
}

void game_loop() {
  while (1) {
    char *player_input = get_string("What do you do? ");

    if (strstr(player_input, "go north") != NULL) {
      generate_room();
    } else if (strstr(player_input, "go east") != NULL) {
      generate_room();
    } else if (strstr(player_input, "go south") != NULL) {
      generate_room();
    } else if (strstr(player_input, "go west") != NULL) {
      generate_room();
    } else if (strstr(player_input, "look around") != NULL) {
      look_around_room();
    } else if (strstr(player_input, "inventory") != NULL) {
      print_inventory();
    } else {
      printf("Even the gods seem puzzled by that request.\n");
    }
  }
}

void delay(int number_of_seconds) {
  int milli_seconds = 1000 * number_of_seconds;

  clock_t start_time = clock();

  // looping till required time is not achieved
  while (clock() < start_time + CLOCKS_PER_SEC)
    ;
}