#include "../include/entity.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear_enemy(Enemy *e);

void add_defense(Entity *ent, int amount) { ent->defense += amount; }

void replace_attack(Entity *ent, int amount) { ent->attack = amount; }

void add_attack(Entity *ent, int amount) {
  if (!ent) {
    fprintf(stderr, "ERROR: add_attack() received NULL Entity pointer!\n");
    return;
  }
  ent->attack += amount;
}

void take_damage(Entity *ent, int amount) {
  if (ent->health - amount <= 0) {
    ent->health = 0;
    check_if_ded(ent);
  } else {
    ent->health -= amount;
  }

  if (ent->health < 0 || ent->health > 1000) {
    ent->health = 0; // clamp
  }
}

void add_health(Entity *ent, int amount) {
  if (ent->health + amount >= ent->max_health) {
    ent->health = ent->max_health;
  } else {
    ent->health += amount;
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
  printf("You assess your condition:\n\n");

  printf("===stats===\n");
  printf("Defense: %i\n", ent.defense);
  printf("Attack: %i\n", ent.attack);
  printf("Health: %i\n", ent.health);
  printf("Stamina: %i\n", ent.stamina);
  printf("===========\n\n");
}

void check_if_ded(Entity *ent) {
  if (ent->health <= 0) {
    if (ent->is_player == false) {
      clear_enemy(ent->owner);
      return;
    } else {
      printf("As your life force fades, the cold grasp of Oblivion takes "
             "hold...\n");
      printf("You have succumbed to the darkness that lurks beyond Tamriel.\n");
      printf("May your soul find peace in the afterlife. Farewell, %s.\n",
             player.name);
      exit(0);
      return;
    }
  }
  return;
}

Entity *init_entity() {
  Entity *new_ent = malloc(sizeof(Entity));
  if (!new_ent) {
    return NULL;
  }

  // 30 is base for attack & stamina
  new_ent->max_health = 30;
  new_ent->health = new_ent->max_health;

  new_ent->max_stamina = 30;
  new_ent->stamina = new_ent->max_stamina;

  new_ent->defense = 10; // base defence
  new_ent->attack = 10;  // base damage

  new_ent->is_player = true;
  new_ent->owner = new_ent;

  player.name = "Dave."; // default name

  return new_ent;
}

Enemy *make_enemy() {
  Enemy *enemy = malloc(sizeof(Enemy));
  enemy->base.is_player = false;
  enemy->base.owner = enemy;

  return enemy;
}

void clear_enemy(Enemy *e) {
  if (!e) {
    return;
  }

  if (e->base.name) {
    free(e->base.name);
    e->base.name = NULL;
  }

  if (e->description) {
    free(e->base.name);
    e->description = NULL;
  }

  memset(e, 0, sizeof(Enemy));
}
