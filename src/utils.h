// utils.h
#ifndef UTILS_H
#define UTILS_H

// Generates a random number between min_value and max_value (inclusive)
int generate_random_number(int min_value, int max_value);

// Prompts user for input (if data is non-NULL, it is printed first),
// then reads a string from stdin (dynamically allocated)
char *get_string(char *data);

// Converts a string to lowercase (modifies in place)
char *lower_player_input(char *input);

#endif // UTILS_H
