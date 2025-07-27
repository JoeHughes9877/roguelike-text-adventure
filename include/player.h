#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
  int health;
  int max_health;
  int stamina;
  int max_stamina;
} Player;

extern Player player;

// Function declarations
void init_player();

void take_damage(int amount);
void add_health(int amount);

void drain_stamina(int amount);
void add_stamina(int amount);

void check_stats();

void check_if_ded();

#endif
