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
  printf("Step 1: Starting to generate items in the room...\n");

  if (items.name != NULL) {
    printf("Step 2: Freeing existing 'name' vector...\n");
    free_vector(items.name);
  } else {
    printf("Step 2: No 'name' vector to free.\n");
  }

  if (items.description != NULL) {
    printf("Step 3: Freeing existing 'description' vector...\n");
    free_vector(items.description);
  } else {
    printf("Step 3: No 'description' vector to free.\n");
  }

  if (items.type != NULL) {
    printf("Step 4: Freeing existing 'type' vector...\n");
    free_vector(items.type);
  } else {
    printf("Step 4: No 'type' vector to free.\n");
  }

  // Randomly generate the number of items in the room
  int min_items = 0;
  int max_items = 4;
  items.num_items_in_room = rand() % (max_items - min_items + 1);
  printf("Step 5: Generated random number of items: %d\n",
         items.num_items_in_room);

  // Open the database
  sqlite3 *DB = NULL;
  open_database(&DB);

  if (DB == NULL) {
    printf("Step 6: Error: Failed to open the database.\n");
    return;
  }
  printf("Step 6: Database opened successfully.\n");

  // SQL query
  char *sql = "SELECT name, description, type FROM item_definitions "
              "ORDER BY RANDOM() "
              "LIMIT ?";

  sqlite3_stmt *stmt;
  sqlite3_prepare_v2(
      DB, sql, -1, &stmt,
      NULL); // -1 allows it to automatically determine length of the SQL string

  if (stmt == NULL) {
    printf("Step 7: Error: Failed to prepare SQL statement.\n");
    sqlite3_close(DB);
    return;
  }
  printf("Step 7: SQL statement prepared successfully.\n");

  sqlite3_bind_int(stmt, 1, items.num_items_in_room);
  printf("Step 8: Bound 'num_items_in_room' (%d) to SQL query.\n",
         items.num_items_in_room);

  for (int i = 0; i < items.num_items_in_room; i++) {
    printf("Step 9: Fetching item %d from database...\n", i);
    int rc = sqlite3_step(stmt);

    if (rc != SQLITE_ROW) {
      printf(
          "Step 9.1: Error: Failed to retrieve item %d from query (rc = %d).\n",
          i, rc);
      continue; // Move to the next iteration if an error occurs
    }
    printf("Step 9.2: Item %d fetched successfully.\n", i);

    const unsigned char *item_name = sqlite3_column_text(stmt, 0);
    const unsigned char *item_description = sqlite3_column_text(stmt, 1);
    const unsigned char *item_type = sqlite3_column_text(stmt, 2);

    if (item_name == NULL || item_description == NULL || item_type == NULL) {
      printf("Step 9.3: Error: One or more columns are NULL for item %d.\n", i);
      continue;
    }
    printf("Step 9.4: Item %d details retrieved: Name = %s, Description = %s, "
           "Type = %s\n",
           i, item_name, item_description, item_type);

    // Allocate memory and copy the values into items structure
    if (item_name != NULL) {
      items.name->elements[i] = strdup((const char *)item_name);
    } else {
      items.name->elements[i] = NULL;
    }

    if (item_description != NULL) {
      items.description->elements[i] = strdup((const char *)item_description);
    } else {
      items.description->elements[i] = NULL;
    }

    if (item_type != NULL) {
      items.type->elements[i] = strdup((const char *)item_type);
    } else {
      items.type->elements[i] = NULL;
    }

    if (items.name->elements[i] == NULL ||
        items.description->elements[i] == NULL ||
        items.type->elements[i] == NULL) {
      printf("Step 9.5: Error: Memory allocation failed for item %d.\n", i);
      continue;
    }
    printf("Step 9.6: Assigned item %d details to the 'items' structure.\n", i);
  }

  sqlite3_finalize(stmt);
  printf("Step 10: Finalized the SQL statement.\n");

  sqlite3_close(DB);
  printf("Step 11: Closed the database.\n");

  printf("Step 12: Completed generating items for the room.\n");
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
  return items_in_room;
}