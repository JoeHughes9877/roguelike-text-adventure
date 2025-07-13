#include "header.h"
#include <sqlite3.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct CurrentRoom room;
struct CurrentItemsInRoom items;

int num_items_in_room;

void generate_room() {

  sqlite3 *DB = NULL;
  open_database(&DB);

  // query to select a row at random
  char *sql = "SELECT name_prefix, name_core, "
              "base_description, possible_features "
              "FROM room_templates "
              "ORDER BY RANDOM() "
              "LIMIT 1;";
  sqlite3_stmt *stmt;

  sqlite3_prepare_v2(
      DB, sql, -1, &stmt,
      NULL); // -1 allows it to automatically determin length of script

  sqlite3_step(stmt);

  room.name_prefix = (char *)sqlite3_column_text(stmt, 0);
  room.name_core = (char *)sqlite3_column_text(stmt, 1);
  room.base_description = (char *)sqlite3_column_text(stmt, 2);

  printf("You find yourself in %s %s, %s\n", room.name_prefix, room.name_core,
         room.base_description);

  sqlite3_close(DB);

  generate_items_in_room();
}

void look_around_room() {
  if (num_items_in_room == 0) {
    printf("you see nothing of value.\n");
  }

  for (int i = 0; i < num_items_in_room; i++) {
    printf("You look around the room and spot %s.\nIt appears to be %s\n",
           items.name[i], items.description[i]);
  }
}

void set_start_room() {
  room.name_prefix = "A grim and foreboding";
  room.name_core = "Imperial City prison cell";
  room.base_description =
      "Cold stone walls and rusty iron bars surround your cell. A "
      "flickering torch casts shadows over a straw-strewn cot. One wall feels "
      "oddly worn, as if it hides more than just years of neglect.";

  num_items_in_room = 0;
}

void generate_items_in_room() {
  // randomly generate the amont of items in a room
  int min_items = 0;
  int max_items = 4;

  // +1 makes it ensures it works within the range
  num_items_in_room = rand() % (max_items - min_items + 1);

  // gets the items from the DB
  sqlite3 *DB = NULL;
  open_database(&DB);

  char *sql = "SELECT name, description, type FROM item_definitions "
              "ORDER BY RANDOM() "
              "LIMIT ?";

  sqlite3_stmt *stmt;

  sqlite3_prepare_v2(
      DB, sql, -1, &stmt,
      NULL); // -1 allows it to automatically determin length of script

  sqlite3_bind_int(stmt, 1, num_items_in_room);

  for (int i = 0; i < num_items_in_room; i++) {
    sqlite3_step(stmt);
    const unsigned char *item_name = sqlite3_column_text(stmt, 0);
    const unsigned char *item_description = sqlite3_column_text(stmt, 1);
    const unsigned char *item_type = sqlite3_column_text(stmt, 2);

    memcpy(&items.name[i], item_name, sizeof(items.name[i]));

    memcpy(&items.description[i], item_description,
           sizeof(items.description[i]));

    memcpy(&items.type[i], item_type, sizeof(items.type[i]));
  }

  sqlite3_finalize(stmt);
  sqlite3_close(DB);
}
int open_database(sqlite3 **DB) {
  int exit = sqlite3_open("data/database.db", DB);
  char *errmsg = "database connection failed.";

  if (exit == 0) {
    return 0;
  } else {
    printf("%s", errmsg);
    return 1;
  }
}