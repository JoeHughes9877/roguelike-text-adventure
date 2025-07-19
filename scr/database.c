#include "database.h"
#include "vector.h"
#include <sqlite3.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct CurrentRoom room;
struct CurrentItemsInRoom items;

int const MAX_ITEMS_IN_ROOM = 4;

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

void generate_items_in_room() {
  // randomly generate the amont of items in a room
  int min_items = 0;
  int max_items = 4;

  // +1 makes it ensures it works within the range
  items.num_items_in_room = rand() % (max_items - min_items + 1);

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

  sqlite3_bind_int(stmt, 1, items.num_items_in_room);

  for (int i = 0; i < items.num_items_in_room; i++) {
    sqlite3_step(stmt);

    const unsigned char *item_name = sqlite3_column_text(stmt, 0);
    const unsigned char *item_description = sqlite3_column_text(stmt, 1);
    const unsigned char *item_type = sqlite3_column_text(stmt, 2);

    items.name->elements[i] =
        strndup((const char *)item_name, sizeof(item_name));

    items.description->elements[i] =
        strndup((const char *)item_description, sizeof(item_description));

    items.type->elements[i] =
        strndup((const char *)item_type, sizeof(item_type));
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

struct vector *init_items() {
  struct vector *items_in_room =
      malloc(sizeof(struct vector) + MAX_ITEMS_IN_ROOM * sizeof(char *));

  items_in_room->size = 0;
  items_in_room->capacity = MAX_ITEMS_IN_ROOM;
  items_in_room->elements = malloc(MAX_ITEMS_IN_ROOM * sizeof(char *));
  items.num_items_in_room = 0;
  return items_in_room;
}