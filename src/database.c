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

int generate_random_number(int min_value, int max_value);

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
  items.num_items_in_room = generate_random_number(0, 4);

  items.name->size = items.num_items_in_room;
  items.description->size = items.num_items_in_room;
  items.type->size = items.num_items_in_room;

  // gets the items from the DB
  sqlite3 *DB = NULL;
  int rc =
      open_database(&DB); // Ensure you check the return value of open_database
  if (rc != SQLITE_OK) {
    printf("Failed to open database: %s\n", sqlite3_errmsg(DB));
    return;
  }

  char *sql = "SELECT name, description, type FROM item_definitions "
              "ORDER BY RANDOM() "
              "LIMIT ?";

  sqlite3_stmt *stmt;
  rc = sqlite3_prepare_v2(
      DB, sql, -1, &stmt,
      NULL); // -1 allows it to automatically determine length of script
  if (rc != SQLITE_OK) {
    printf("Failed to prepare statement: %s\n", sqlite3_errmsg(DB));
    sqlite3_close(DB);
    return;
  }

  sqlite3_bind_int(stmt, 1, items.num_items_in_room);

  for (int i = 0; i < items.num_items_in_room; i++) {
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW) {
      printf("Error stepping through result: %s\n", sqlite3_errmsg(DB));
      break; // Exit loop if there's an issue with fetching the result
    }

    const unsigned char *item_name = sqlite3_column_text(stmt, 0);
    const unsigned char *item_description = sqlite3_column_text(stmt, 1);
    const unsigned char *item_type = sqlite3_column_text(stmt, 2);

    items.name->elements[i] =
        strndup((const char *)item_name, strlen((char *)item_name));
    items.description->elements[i] = strndup((const char *)item_description,
                                             strlen((char *)item_description));
    items.type->elements[i] =
        strndup((const char *)item_type, strlen((char *)item_type));
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
  items.num_items_in_room = 0;

  items_in_room->elements = malloc(MAX_ITEMS_IN_ROOM * sizeof(char *));
  for (int i = 0; i < MAX_ITEMS_IN_ROOM; i++) {
    items_in_room->elements[i] = NULL; // Initialize each pointer to NULL
  }

  return items_in_room;
}

void free_items_from_room() {

  for (int i = 0; i < items.num_items_in_room; i++) {
    free(items.name->elements[i]);
    free(items.description->elements[i]);
    free(items.type->elements[i]);
  }
}
