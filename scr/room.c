#include "database.h"
#include "vector.h"
#include <stdio.h>
#include <string.h>

void look_around_room() {
  if (items.num_items_in_room == 0) {
    printf("you see nothing of value.\n");
  }

  for (int i = 0; i < items.num_items_in_room; i++) {
    printf("You look around the room and spot %s.\nIt appears to be %s\n",
           items.name->elements[i], items.description->elements[i]);
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
