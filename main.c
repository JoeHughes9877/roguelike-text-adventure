#include "header.h"
#include <stdio.h>

void opening();

int main() {
  opening();

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
