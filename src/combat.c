#include "../include/database.h"
#include "../include/entity.h"
#include "../include/utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool in_combat = false;

// all rolls are based off a D20 dice.
// ent_one is the attacker

void attack_roll(Entity *ent_one, Enemy *ent_two) {
  int attack_roll = generate_random_number(1, 20);
  printf("Attacker rolled: %i\n", attack_roll);
  int defence_roll = generate_random_number(1, 20);
  printf("Defender rolled: %i\n", defence_roll);

  int attack_success_chance = ent_one->attack + attack_roll;
  int defence_success_chance = ent_two->base.attack + defence_roll;

  if (attack_success_chance > defence_success_chance) {
    printf("Hit!\n");
    take_damage(&ent_two->base, ent_one->attack);

    if (ent_two->base.health <= 0) {
      in_combat = false;
    }
    printf("Base attack (damage amount): %d\n", ent_one->attack);
    printf("health is now: %i\n", ent_two->base.health);
  } else {
    printf("Missed!\n");
  }
}

void Flee(Entity *ent) {
  int roll = generate_random_number(1, 20);
  printf("Fleer Rolled: %i\n", roll);

  int flee_success_chance = ent->stamina + roll;

  // 30 is just a random number i chose will need to be changed later
  if (flee_success_chance > 110) {
    printf("Tactical retreat. \n");
    in_combat = false;
    return;
  } else {
    printf("Attempt unsuccessful. Now you just look like a pussy.\n");
    return;
  }
}

void combat_loop(char *enemy) {
  in_combat = true;

  Enemy *enemy_pointer = locate_enemy(enemy);

  if (enemy_pointer == NULL) {
    in_combat = false;
  }

  printf("\nName: %s\n", enemy_pointer->name);
  printf("--- Stats ---\n");
  printf("Vitality : %d\n", enemy_pointer->base.health);
  printf("Might    : %d\n", enemy_pointer->base.attack);
  printf("Guard    : %d\n", enemy_pointer->base.defense);
  printf("XP Bounty: %d\n", enemy_pointer->xp_reward);
  printf("-------------\n");

  while (in_combat) {
    char *player_input = get_string("What's your next move: ");

    player_input = lower_player_input(player_input);

    if (strstr(player_input, "attack") != NULL) {
      attack_roll(&player, enemy_pointer);
    } else if (strstr(player_input, "flee") != NULL) {
      Flee(&player);
    } else {
      printf("Really? You want to try that now, of all times?\n");
    }
  }

  printf("\nVictorious or defeated, the battle is over.\n");
}