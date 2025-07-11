#include "header.h"
#include <sqlite3.h>
#include <stddef.h>
#include <stdio.h>

struct CurrentRoom generate_room() {
  struct CurrentRoom room;

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

  printf("%s\n", room.name_prefix);
  printf("%s\n", room.name_core);
  printf("%s\n", room.base_description);

  return room;
}