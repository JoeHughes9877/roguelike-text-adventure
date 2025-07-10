#include "header.h"
#include <stdio.h>
#include <time.h>

void opening();
void delay(int number_of_seconds);

int main() {
  opening();

  printf("\nThe threads of fate twist around you...");
  printf("\nBut before your journey begins — tell me: who are you? ");
  char *name = get_string();

  delay(3);

  printf("With the taste of freedom fresh on your lips, what path will you "
         "take? ");
  get_string();
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
         "collapsed.\n");
  printf("  Screams echo down the corridor... and your cell door creaks "
         "open.\n\n");
  printf("  Freedom — unexpected and unearned — lies before you.\n");

  printf("---------------------------------------------------------------------"
         "----------\n");
}

void delay(int number_of_seconds) {
  int milli_seconds = 1000 * number_of_seconds;

  clock_t start_time = clock();

  // looping till required time is not achieved
  while (clock() < start_time + CLOCKS_PER_SEC)
    ;
}