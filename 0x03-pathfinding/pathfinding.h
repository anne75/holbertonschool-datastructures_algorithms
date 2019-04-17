#ifndef _PATHFINDING_H_
#define _PATHFINDING_H_

#include <stdio.h>
#include <stdlib.h>

#include "libraries/0x07-pathfinding.c/graphs.h"
#include "libraries/0x07-pathfinding.c/queues.h"

/**
 * struct point_s - Structure storing coordinates
 *
 * @x: X coordinate
 * @y: Y coordinate
 */
typedef struct point_s
{
	int x;
	int y;
} point_t;

/**
 * enum direction_e - Directions allowed in the grid.
 * @RIGHT: move right.
 * @BOTTOM: move down.
 * @LEFT: move left.
 * @TOP: move up.
 */
enum direction_e
{
	RIGHT = 0,
	BOTTOM,
	LEFT,
	TOP
};

/* backtracking array */
queue_t *backtracking_array(char **map, int rows, int cols,
			    point_t const *start, point_t const *target);


#endif
