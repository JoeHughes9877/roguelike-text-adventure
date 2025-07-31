#ifndef ENTITY_H
#define ENTITY_H

#include "../include/entity.h"

// Function declarations
void attack_enemy(Entity *ent_one, Entity *ent_two);
void defend(Entity *ent_one, Entity *ent_two);
void Flee(Entity *ent);
void combat_loop();

#endif // ENTITY_H