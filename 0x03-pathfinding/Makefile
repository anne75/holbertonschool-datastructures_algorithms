CC = gcc-4.8
CFLAGS = -Wall -Wextra -Werror -pedantic
LIBRARIES = -L ./libraries/0x07-pathfinding.c/

quest_0:
	$(CC) $(CFLAGS) -g $(LIBRARIES) tests/0-main.c 0-backtracking_array.c  -lgraphs -lqueues

quest_1:
	$(CC) $(CFLAGS) -g $(LIBRARIES) tests/1-main.c 1-backtracking_graph.c  -lgraphs -lqueues

clean:
	rm *.out
