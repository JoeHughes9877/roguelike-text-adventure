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
  char name[4][32];
  char description[4][256];
  char type[4][32];
  int num_items_in_room;
};

extern struct CurrentRoom room;
extern struct CurrentItemsInRoom items;

// functions from get_inputs.c
char *get_string(char *data);

// database
extern sqlite3 *db;

// Functions from database handling
void generate_room();
void look_around_room();
void set_start_room();
void generate_items_in_room();
int open_database(sqlite3 **DB);

#endif