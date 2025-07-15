#include "database.h"
#include "vector.h"
#include <stdio.h>

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