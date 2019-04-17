CC = gcc-4.8
CFLAGS = -Wall -Wextra -Werror -pedantic
LIBRARIES = -L ./libraries/0x07-pathfinding.c/

quest_0:
	$(CC) -g $(LIBRARIES) tests/0-main.c 0-backtracking_array.c  -lgraphs -lqueues

clean:
	rm *.out
