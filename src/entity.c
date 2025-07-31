#include "../include/entity.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void add_defense(Entity *ent, int amount) { ent->defense += amount; }

void replace_attack(Entity *ent, int amount) { ent->attack = amount; }

void add_attack(Entity *ent, int amount) { ent->attack += amount; }

void take_damage(Entity *ent, int amount) {
  printf("Damage dealt: %d\n", amount);

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
      free_enemy(ent->owner);
      return;
    } else {
      printf("As your life force fades, the cold grasp of Oblivion takes "
             "hold...\n");
      printf("You have succumbed to the darkness that lurks beyond Tamriel.\n");
      printf("May your soul find peace in the afterlife. Farewell, brave "
             "adventurer.\n");
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

  return new_ent;
}

Enemy *make_enemy() {
  Enemy *enemy = malloc(sizeof(Enemy));
  enemy->base.is_player = false;
  enemy->base.owner = &enemy;

  return enemy;
}

// the space is reused so it's not acctually freed just replaced.
void free_enemy(Enemy *enemy) {
  if (!enemy)
    return;

  printf("name: %s\n", enemy->name);
  printf("desd, %s\n", enemy->description);
}
