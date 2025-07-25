CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11 -g -I./src
OBJ = src/main.c src/database.c src/inventory.c src/room.c src/utils.c src/vector.c
OUT = game

all:
	$(CC) $(CFLAGS) $(OBJ) -o $(OUT)

clean:
	rm -f $(OUT)
