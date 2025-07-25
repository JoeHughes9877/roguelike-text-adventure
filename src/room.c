#include "../include/database.h"
#include "../include/utils.h"
#include "../include/vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_opposite(char *dir);

// definition
char *exits_in_room[4];
int num_of_exits = 0;

char *directions[] = {"north", "east", "south", "west"};
char *opposites[] = {"south", "west", "north", "east"};

void look_around_room() {
  if (items.num_items_in_room == 0) {
    printf("You look around but see nothing of value.\n");
  } else {
    printf("As you look around, you notice:\n");
    for (int i = 0; i < items.num_items_in_room; i++) {
      printf(" - %s: %s\n", items.name->elements[i],
             items.description->elements[i]);
    }
  }

  if (num_of_exits > 0) {
    printf("\nExits:\n");
    for (int j = 0; j < num_of_exits; j++) {
      printf(" - %s\n", exits_in_room[j]);
    }
  } else {
    printf("\nThere are no visible exits.\n");
  }
}

void set_start_room() {
  room.name_prefix = "A grim and foreboding";
  room.name_core = "Imperial City prison cell";
  room.base_description =
      "Cold stone walls and rusty iron bars surround your cell. A "
      "flickering torch casts shadows over a straw-strewn cot. One wall feels "
      "oddly worn, as if it hides more than just years of neglect.";

  items.num_items_in_room = 0;

  num_of_exits = 2;
  exits_in_room[0] = "north";
  exits_in_room[1] = "west";
}

void remove_item_from_room(char *item) {
  for (int i = 0; i < items.num_items_in_room; i++) {
    if (strcmp(items.name->elements[i], item) == 0) {
      items.name = delete_by_index(items.name, i);
      items.description = delete_by_index(items.description, i);
      items.type = delete_by_index(items.type, i);

      items.num_items_in_room--;
      return;
    }
  }

  // If item wasn't found
  printf("Item %s not found in room.\n", item);
}

void generate_exits_in_room(char *entry_direction) {
  char *temp_dir[4];
  for (int i = 0; i < 4; i++) {
    temp_dir[i] = directions[i];
  }

  // fisher yates shuffle
  for (int i = num_of_exits - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    char *tmp = directions[j];
    temp_dir[j] = temp_dir[i];
    temp_dir[i] = tmp;
  }

  num_of_exits = generate_random_number(1, 3) + 1;
  for (int i = 0; i < num_of_exits; i++) {
    exits_in_room[i] = temp_dir[i];
  }

  char *required_exit = get_opposite(entry_direction);
  int found = 0;
  for (int i = 0; i < num_of_exits; i++) {
    if (strcmp(exits_in_room[i], required_exit) == 0) {
      found = 1;
      break;
    }
  }

  if (!found && required_exit != NULL) {
    exits_in_room[0] = required_exit;
  }
}

int can_go_dir(char *direction) {
  if (direction == NULL)
    return 0;
  for (int i = 0; i < 4; i++) {
    if (exits_in_room[i] == NULL)
      continue;
    if (strcmp(direction, exits_in_room[i]) == 0) {
      return 1;
    }
  }
  return 0;
}

char *get_opposite(char *dir) {
  for (int i = 0; i < 4; i++) {
    if (strcmp(directions[i], dir) == 0) {
      return opposites[i];
    }
  }
  return NULL;
}