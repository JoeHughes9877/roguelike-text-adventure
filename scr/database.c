#include "header.h"
#include <sqlite3.h>
#include <stddef.h>
#include <stdio.h>

struct CurrentRoom room;

struct CurrentRoom generate_room() {

  // opens database
  sqlite3 *DB;
  int exit = 0;
  exit = sqlite3_open("data/database.db", &DB);
  char *errmsg = "database connection failed.";

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

  // room.possible_features = (char *)sqlite3_value_text(3);
  //  unimplemented feature as not sure how to handle it yet.

  printf("You find yourself in %s %s, %s\n", room.name_prefix, room.name_core,
         room.base_description);

  return room;
}

void look_around_room() {

  // if the rooms name is Null then i assume that the entire struct is also Null
  // so i need to generate a new room
  if (room.name_core == NULL) {
    generate_room();
  }

  printf("You find yourself in %s %s, %s\n", room.name_prefix, room.name_core,
         room.base_description);
}

void set_start_room() {
  room.name_prefix = "A grim and foreboding";
  room.name_core = "Imperial City prison cell";
  room.base_description =
      "Cold stone walls and rusty iron bars surround your cell. A "
      "flickering torch casts shadows over a straw-strewn cot. One wall feels "
      "oddly worn, as if it hides more than just years of neglect.";
}