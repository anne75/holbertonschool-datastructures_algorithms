#include "pathfinding.h"

/**
 * point_is_valid - checks a point is a valid place to go.
 * @map: grid on which the maze is.
 * @rows: number of rows in the maze.
 * @cols: number of columns in the maze.
 * @to_check: the point we want to check
 * It is assumed the map is a valid argument.
 * Return: 1 if the move is valid, 0 otherwise.
 */
int point_is_valid(char **map, int rows, int cols, queue_t *path,
		   const point_t *to_check)
{
	queue_node_t *element;
	point_t *value;

	if (!to_check)
		return (0);
	if (to_check->x < 0 || to_check->x >= cols)
		return (0);
	if (to_check->y < 0 || to_check->y >= rows)
		return (0);
	if (map[to_check->y][to_check->x] == '1')
		return (0);
	if (path)
	{
		element = path->front;
		while (element)
		{
			value = (point_t *)element->ptr;
			if (value->x == to_check->x && value->y == to_check->y)
				return (0);
			element = element->next;
		}
	}
	return (1);
}

/**
 * next_point - Get the next point for a given point and direction.
 * @present_point: point we are on.
 * @direction: direction we want to move to.
 * Return: a point that may not be a valid move, NULL on failure.
 */
point_t *next_point(const point_t *present_point, int direction)
{
	/* assume all arguments are valid */
	point_t *next;

	next = malloc(sizeof(point_t));
	if (!next)
		return (NULL);

	next->x = present_point->x;
	next->y = present_point->y;

	switch (direction)
	{
	case RIGHT:
		++next->x;
		break;
	case BOTTOM:
		++next->y;
		break;
	case LEFT:
		--next->x;
		break;
	case TOP:
		--next->y;
		break;
	default:
		free(next);
		next = NULL;
	}
	return (next);
}

/**
 * recursive_call - Core of the backtracking algorithm.
 * @map: maze grid.
 * @rows: number of rows on the grid.
 * @cols: number of columns on the grid.
 * @already_seen: queue of elements we have already looked at.
 * @path: the end result, the successfull path from start to end.
 * @start: starting point to consider.
 * @target: end point.
 * Return: 1 if a successfull path was found from start, 0 otherwise.
 */
int recursive_call(char **map, int rows, int cols, queue_t *already_seen,
			queue_t *path, point_t *start, point_t *target)
{
	point_t *next;
	int direction, recursion_success;

	printf("Checking coordinates [%d, %d]\n", start->x, start->y);
	if (start->x == target->x && start->y == target->y)
		return (1);

	recursion_success = 0;
	for (direction = 0; direction < 4; ++direction)
	{
		next = next_point(start, direction);
		if (!next)
			continue;
		if (!point_is_valid(map, rows, cols, already_seen, next))
		{
			free(next);
			continue;
		}
		queue_push_front(already_seen, (void *)next);
		recursion_success = recursive_call(map, rows, cols,
						   already_seen, path,
						   next, target);
		if (recursion_success)
		{
			queue_push_front(path, next);
			break;
		}
		else
		{
			dequeue(already_seen);
			free(next);
		}
	}
	return (recursion_success);
}

/**
 * free_path - free all the elements in a queue and the queue itself.
 * @path: a queue.
 */
void free_path(queue_t *path)
{
	point_t *point;

	while (path->front)
	{
		point = (point_t *)dequeue(path);
		free(point);
	}
	free(path);
}

/**
 * backtracking_array - entrypoint for the backtracking algorithm.
 * @map: maze grid.
 * @rows: number of rows on the grid.
 * @cols: number of columns on the grid.
 * @start: starting point.
 * @target: end point.
 * Return: path on success , NULL on failure or if no path was found.
 */
queue_t *backtracking_array(char **map, int rows, int cols,
			    point_t const *start, point_t const *target)
{
	queue_t *path, *already_seen;
	queue_node_t *node;
	point_t *start_copy;
	int recursion_success;

	if (!map || !*map || !rows || !cols || !start || !target)
		return (NULL);
	if (!(point_is_valid(map, rows, cols, NULL, start) &&
	      point_is_valid(map, rows, cols, NULL, target)))
		return (NULL);
	path = queue_create();
	if (!path)
		return (NULL);
	already_seen = queue_create();
	if (!already_seen)
	{
		queue_delete(path);
		return (NULL);
	}
	node = queue_push_front(already_seen, (void *)start);
	if (!node)
	{
		queue_delete(path), queue_delete(already_seen);
		return (NULL);
	}

	recursion_success = recursive_call(map, rows, cols, already_seen, path,
					   (point_t *)start, (point_t *)target);
	queue_delete(already_seen);
	if (!recursion_success)
		free_path(path), path = NULL;
	else
	{
		start_copy = malloc(sizeof(point_t));
		if (!start_copy)
			free_path(path), path = NULL;
		start_copy->x = start->x, start_copy->y = start->y;
		queue_push_front(path, start_copy);
	}
	return (path);
}
