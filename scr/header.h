#ifndef HEADER_H
#define HEADER_H

#include <sqlite3.h>

struct CurrentRoom {
  char *name_prefix;
  char *name_core;
  char *base_description;
  char *features;
};

// functions from get_inputs.c
char *get_string();

// database
extern sqlite3 *db;

// Functions from database handling
struct CurrentRoom generate_room();

#endif