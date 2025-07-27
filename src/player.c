#include "../include/player.h"
#include <stdio.h>
#include <stdlib.h>

Player player;

void take_damage(int amount) {
  if (player.health - amount <= 0) {
    player.health = 0;
  } else {
    player.health -= amount;
  }
}

void add_health(int amount) {
  if (player.health + amount >= player.max_health) {
    player.health = player.max_health;
  } else {
    player.health += amount;
  }
}

void drain_stamina(int amount) {
  if (player.stamina - amount <= 0) {
    player.stamina = 0;
  } else {
    player.stamina -= amount;
  }
}
void add_stamina(int amount) {
  if (player.stamina + amount >= player.max_stamina) {
    player.stamina = player.max_stamina;
  } else {
    player.stamina += amount;
  }
}

void check_stats() {
  printf("You assess your condition:\n");

  // Health status
  if (player.health >= 75) {
    printf("You’re in good shape, with %d health.\n", player.health);
  } else if (player.health >= 50) {
    printf("You’re hurt, but still standing. (%d health)\n", player.health);
  } else if (player.health >= 25) {
    printf("Your wounds are serious; you need to be careful. (%d health)\n",
           player.health);
  } else {
    printf("You’re badly injured and near death. (%d health)\n", player.health);
  }

  // Stamina status
  if (player.stamina >= 75) {
    printf("Your stamina is high, ready for whatever comes. (%d stamina)\n",
           player.stamina);
  } else if (player.stamina >= 50) {
    printf("You’re a bit tired, but can keep going. (%d stamina)\n",
           player.stamina);
  } else if (player.stamina >= 25) {
    printf("Fatigue is setting in; rest soon. (%d stamina)\n", player.stamina);
  } else {
    printf("You’re exhausted and need to recover. (%d stamina)\n",
           player.stamina);
  }
}

void check_if_ded() {
  if (player.health <= 0) {
    printf(
        "As your life force fades, the cold grasp of Oblivion takes hold...\n");
    printf("You have succumbed to the darkness that lurks beyond Tamriel.\n");
    printf("May your soul find peace in the afterlife. Farewell, brave "
           "adventurer.\n");
    exit(0);
  }
}

void init_player() {
  player.max_health = 100;
  player.health = player.max_health;

  player.max_stamina = 100;
  player.stamina = player.max_stamina;
}