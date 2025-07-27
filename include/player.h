#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
  int health;
  int max_health;
  int stamina;
  int max_stamina;
} Player;

// Function declarations
void init_player(Player *player);

void take_damage(Player *player, int amount);
void add_health(Player *player, int amount);

void drain_stamina(Player *player, int amount);
void add_stamina(Player *player, int amount);

void check_stats(const Player *player);

void check_if_ded(Player *player, int health);

#endif
