#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
  int health;
  int max_health;
  int stamina;
  int max_stamina;
  int attack;
  int defense;
} Entity;

typedef struct {
  Entity base;
  char *name;
  char *description;
  int xp_reward;
} Enemy;

// Function declarations
Entity *init_entity();

void take_damage(Entity ent, int amount);
void add_health(Entity ent, int amount);

void drain_stamina(Entity ent, int amount);
void add_stamina(Entity ent, int amount);

void check_stats(Entity ent);

void check_if_ded(Entity ent);

void free_entity(Entity *ent);

Enemy *make_enemy();
#endif
