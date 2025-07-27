#include "../include/entity.h"
#include <stdio.h>
#include <stdlib.h>

void take_damage(Entity ent, int amount) {
  if (ent.health - amount <= 0) {
    ent.health = 0;
  } else {
    ent.health -= amount;
  }
  check_if_ded(ent);
}

void add_health(Entity ent, int amount) {
  if (ent.health + amount >= ent.max_health) {
    ent.health = ent.max_health;
  } else {
    ent.health += amount;
  }
}

void drain_stamina(Entity ent, int amount) {
  if (ent.stamina - amount <= 0) {
    ent.stamina = 0;
  } else {
    ent.stamina -= amount;
  }
}

void add_stamina(Entity ent, int amount) {
  if (ent.stamina + amount >= ent.max_stamina) {
    ent.stamina = ent.max_stamina;
  } else {
    ent.stamina += amount;
  }
}

void check_stats(Entity ent) {
  printf("You assess your condition:\n");

  // Health status
  if (ent.health >= 75) {
    printf("You’re in good shape, with %d health.\n", ent.health);
  } else if (ent.health >= 50) {
    printf("You’re hurt, but still standing. (%d health)\n", ent.health);
  } else if (ent.health >= 25) {
    printf("Your wounds are serious; you need to be careful. (%d health)\n",
           ent.health);
  } else {
    printf("You’re badly injured and near death. (%d health)\n", ent.health);
  }

  // Stamina status
  if (ent.stamina >= 75) {
    printf("Your stamina is high, ready for whatever comes. (%d stamina)\n",
           ent.stamina);
  } else if (ent.stamina >= 50) {
    printf("You’re a bit tired, but can keep going. (%d stamina)\n",
           ent.stamina);
  } else if (ent.stamina >= 25) {
    printf("Fatigue is setting in; rest soon. (%d stamina)\n", ent.stamina);
  } else {
    printf("You’re exhausted and need to recover. (%d stamina)\n", ent.stamina);
  }
}

// player death currently, will end game on any death including enemy
void check_if_ded(Entity ent) {
  if (ent.health <= 0) {
    printf(
        "As your life force fades, the cold grasp of Oblivion takes hold...\n");
    printf("You have succumbed to the darkness that lurks beyond Tamriel.\n");
    printf("May your soul find peace in the afterlife. Farewell, brave "
           "adventurer.\n");

    free_entity(&ent);
    exit(0);
  }
}

Entity *init_entity() {
  Entity *new_ent = malloc(sizeof(Entity));
  if (!new_ent) {
    return NULL;
  }

  new_ent->max_health = 100;
  new_ent->health = new_ent->max_health;

  new_ent->max_stamina = 100;
  new_ent->stamina = new_ent->max_stamina;

  return new_ent;
}

void free_entity(Entity *ent) { free(ent); }