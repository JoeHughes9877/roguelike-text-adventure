#ifndef DATABASE_H
#define DATABASE_H

#include "vector.h"
#include <sqlite3.h>

struct CurrentRoom {
  char *name_prefix;
  char *name_core;
  char *base_description;
  char *features;
};

struct CurrentItemsInRoom {
  struct vector *name;
  struct vector *description;
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
void generate_items_in_room();
int open_database(sqlite3 **DB);
int generate_random_number(int min_value, int max_value);

// initalise items struct
struct vector *init_items();

// freeing memory
void free_items_from_room();

int generate_random_number(int min_value, int max_value);

void generate_enemies_in_room(void);

#endif