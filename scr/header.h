#ifndef HEADER_H
#define HEADER_H

#include <sqlite3.h>

struct CurrentRoom {
  char *name_prefix;
  char *name_core;
  char *base_description;
  char *features;
};

struct CurrentItemsInRoom {
  char name[4];
  char description[4];
  char type[4];
};

// functions from get_inputs.c
char *get_string(char *data);

// database
extern sqlite3 *db;

// Functions from database handling
void generate_room();
void look_around_room();
void set_start_room();
int items_in_room();
int open_database(sqlite3 **DB);

#endif