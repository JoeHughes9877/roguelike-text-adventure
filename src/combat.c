#include "../include/database.h"
#include "../include/entity.h"
#include "../include/items.h"
#include "../include/utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool in_combat = false;
Enemy *enemy_pointer = NULL;

void enemy_turn(Entity *player, Enemy *enemy);

void attack_roll(Entity *ent_one, Entity *ent_two, int damage) {
  int attack_roll = generate_random_number(1, 20);
  int defence_roll = generate_random_number(1, 20);

  int attack_success_chance = damage + attack_roll;
  int defence_success_chance = ent_two->defense + defence_roll;

  printf("\n-- Combat Roll --\n");
  printf("Attacker (%s) rolled: %d (Total: %d)\n", ent_one->name, attack_roll,
         attack_success_chance);
  printf("Defender (%s) rolled: %d (Total: %d)\n", ent_two->name, defence_roll,
         defence_success_chance);

  if (attack_success_chance > defence_success_chance) {
    printf("=> HIT! %s deals %d damage to %s!\n", ent_one->name, damage,
           ent_two->name);
    take_damage(ent_two, damage);
    printf("%s's health is now: %d\n", ent_two->name, ent_two->health);

    if (ent_two->health <= 0) {
      printf("%s has fallen!\n", ent_two->name);
      in_combat = false;
    }
  } else {
    printf("=> MISS! %s evades the attack.\n", ent_two->name);
  }
  printf("-------------------\n");
}

void Flee(Entity *ent) {
  int roll = generate_random_number(1, 20);
  int flee_success_chance = ent->stamina + roll;

  printf("\n-- Flee Attempt --\n");
  printf("%s rolls: %d (Total: %d)\n", ent->name, roll, flee_success_chance);

  if (flee_success_chance > 110) {
    printf("=> SUCCESS! %s makes a tactical retreat.\n", ent->name);
    in_combat = false;
  } else {
    printf("=> FAILURE! %s couldn't escape the battle.\n", ent->name);
  }
  printf("-------------------\n");
}

void combat_loop(char *enemy) {
  in_combat = true;

  enemy_pointer = locate_enemy(enemy);
  if (enemy_pointer == NULL) {
    printf("No such enemy found.\n");
    in_combat = false;
    return;
  }

  printf("\n==== Encounter Begins ====\n");
  printf("You face: %s\n", enemy_pointer->base.name);
  printf("Vitality : %d\n", enemy_pointer->base.health);
  printf("Might    : %d\n", enemy_pointer->base.attack);
  printf("Guard    : %d\n", enemy_pointer->base.defense);
  printf("XP Bounty: %d\n", enemy_pointer->xp_reward);
  printf("==========================\n");

  while (in_combat) {
    printf("\n--- Your Turn ---\n");
    char *player_input = get_string("What's your next move (attack/flee)? ");
    player_input = lower_player_input(player_input);

    if (strstr(player_input, "attack") != NULL) {
      attack_roll(&player, &enemy_pointer->base, player.attack);
    } else if (strstr(player_input, "flee") != NULL) {
      Flee(&player);
    } else if (strstr(player_input, "use") != NULL) {
      use_item(player_input);
    } else {
      printf("Really you want to try that now?.\n");
    }

    if (in_combat) {
      enemy_turn(&player, enemy_pointer);
    }
  }

  printf("\n=== Combat Ends ===\n");
}

void enemy_turn(Entity *player, Enemy *enemy) {
  printf("\n--- Enemy Turn ---\n");

  if (enemy->base.health < enemy->base.max_health * 0.2) {
    printf("%s looks injured and tries to flee!\n", enemy->base.name);
    Flee(&enemy->base);
  } else {
    attack_roll(&enemy->base, player, enemy->base.attack);
  }

  printf("-------------------\n");
}
