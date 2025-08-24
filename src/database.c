#include "../include/database.h"
#include "../include/entity.h"
#include "../include/room.h"
#include "../include/utils.h"
#include <sqlite3.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct CurrentRoom room;
struct CurrentItemsInRoom items;

int const MAX_ITEMS_IN_ROOM = 4;

void generate_enemies_in_room(void);

int generate_random_number(int min_value, int max_value);

int num_of_enemies_in_room = 0;
Enemy *enemies_in_room[2];

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
  generate_enemies_in_room();
}

void generate_items_in_room() {
  destroy_room_contents();

  items.name = init_items();
  items.description = init_items();

  items.num_items_in_room = generate_random_number(0, 4);

  items.name->size = items.num_items_in_room;
  items.description->size = items.num_items_in_room;

  // gets the items from the DB
  sqlite3 *DB = NULL;
  int rc = open_database(&DB);
  if (rc != SQLITE_OK) {
    printf("Failed to open database: %s\n", sqlite3_errmsg(DB));
    return;
  }

  char *sql = "SELECT name, description FROM item_definitions "
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

    const unsigned char *collumns[3];
    for (int col = 0; col < 3; col++) {
      collumns[col] = sqlite3_column_text(stmt, col);
    }

    items.name->elements[i] =
        strndup((const char *)collumns[0], strlen((char *)collumns[0]));
    items.description->elements[i] =
        strndup((const char *)collumns[1], strlen((char *)collumns[1]));
  }

  sqlite3_finalize(stmt);
  sqlite3_close(DB);
}

void generate_enemies_in_room(void) {
  num_of_enemies_in_room =
      generate_random_number_bias(1, 3, 0.65); // 0.7 (65% chance),

  for (int i = 0; i < num_of_enemies_in_room; i++) {
    enemies_in_room[i] = make_enemy();
  }

  // gets the items from the DB
  sqlite3 *DB = NULL;
  int rc = open_database(&DB);
  if (rc != SQLITE_OK) {
    printf("Failed to open database: %s\n", sqlite3_errmsg(DB));
    return;
  }

  char *sql = "SELECT name, description, base_health, base_attack, "
              "base_defense, xp_reward FROM "
              "enemy_definitions " // Explicitly select columns for clarity
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

  sqlite3_bind_int(stmt, 1, num_of_enemies_in_room);

  if (num_of_enemies_in_room == 0) {
    sqlite3_finalize(stmt);
    sqlite3_close(DB);
    return;
  }

  printf("\nYou’re not alone.\n");

  for (int i = 0; i < num_of_enemies_in_room; i++) {
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW) {
      printf("Error stepping through result: %s\n", sqlite3_errmsg(DB));
      break; // Exit loop if there's an issue with fetching the result
    }

    const unsigned char *columns[6];
    for (int col = 0; col < 6; col++) {
      columns[col] = sqlite3_column_text(stmt, col);
    }

    enemies_in_room[i]->base.name =
        strdup((const char *)sqlite3_column_text(stmt, 0));
    enemies_in_room[i]->description =
        strdup((const char *)sqlite3_column_text(stmt, 1));
    enemies_in_room[i]->base.health = sqlite3_column_int(stmt, 2);
    enemies_in_room[i]->base.attack = sqlite3_column_int(stmt, 3);
    enemies_in_room[i]->base.defense = sqlite3_column_int(stmt, 4);
    enemies_in_room[i]->xp_reward = sqlite3_column_int(stmt, 5);
    enemies_in_room[i]->base.stamina = sqlite3_column_int(stmt, 6);

    printf("Name: %s\n", enemies_in_room[i]->base.name);
    printf("Description: %s\n\n", enemies_in_room[i]->description);
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
  }
}
