#ifndef ROOM_H
#define ROOM_H

#include "database.h"

void set_start_room();
void look_around_room();
void remove_item_from_room(char *item);
void generate_exits_in_room(char *entry_direction);

#endif