#include "../include/player.h"

void take_damage(Player *player, int amount) {}
void add_health(Player *player, int amount) {}

void drain_stamina(Player *player, int amount) {}
void add_stamina(Player *player, int amount) {}

void check_stats(const Player *player) {}

void check_if_ded(Player *player, int health) {}

void init_player(Player *player) {
  player->max_health = 100;
  player->health = player->max_health;

  player->max_stamina = 100;
  player->stamina = player->max_stamina;
}