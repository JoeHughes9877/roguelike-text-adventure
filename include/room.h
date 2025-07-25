#ifndef ROOM_H
#define ROOM_H

void set_start_room(void);
void look_around_room(void);
void remove_item_from_room(char *item);
void generate_exits_in_room(char *entry_direction);
int can_go_dir(char *direction);

#endif
