#ifndef ENTITY_H
#define ENTITY_H

#include "../include/entity.h"

extern bool in_combat;
extern Enemy *enemy_pointer;

// Function declarations
void attack_roll(Entity *ent_one, Entity *ent_two, int damage);
void defend(Entity *ent_one, Entity *ent_two);
void Flee(Entity *ent);
void combat_loop();

#endif // ENTITY_H