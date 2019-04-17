#include "pathfinding.h"


int point_is_valid(char **map, int rows, int cols, queue_t *path,
		   const point_t *to_check)
{
	queue_node_t *element;
	point_t *value;

	if (!to_check) return (0);

	if (to_check->x < 0 || to_check->x >= cols) return (0);
	if (to_check->y < 0 || to_check->y >= rows) return (0);
	if (map[to_check->y][to_check->x] == '1') return (0);
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

point_t *next_point(char **map, int rows, int cols, queue_t *path,
		    const point_t *present_point, int direction)
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
		if (point_is_valid(map, rows, cols, path, (const point_t *)next))
			return next;
		break;
	case BOTTOM:
		++next->y;
		if (point_is_valid(map, rows, cols, path, (const point_t *)next))
			return next;
		break;
	case LEFT:
		--next->x;
		if (point_is_valid(map, rows, cols, path, (const point_t *)next))
			return next;
		break;
	case TOP:
		--next->y;
		if (point_is_valid(map, rows, cols, path, (const point_t *)next))
			return next;
		break;
	}
	free(next);
	return (NULL);
}


point_t *recursive_call(char **map, int rows, int cols, queue_t *already_seen,
			queue_t *path, point_t *start, point_t *target)
{
	queue_node_t *node;
	point_t *tmp_point, *next;
	int direction;

	printf("Checking coordinates [%d, %d]\n", start->x, start->y);
	if (start->x == target->x && start->y == target->y)
		return (start);

	for (direction = 0; direction < 4; ++direction)
	{
		next = next_point(map, rows, cols, already_seen, start,
				  direction);
		if (!next)
			continue;
		node = already_seen->front;
		queue_push_front(already_seen, (void *)next);
		tmp_point = recursive_call(map, rows, cols, already_seen, path,
					   next, target);
		if (tmp_point)
		{
			queue_push_front(path, next);
			return (start);
		}
		else
		{
			dequeue(already_seen);
			free(next);
		}
	}
	return (NULL);
}


queue_t *backtracking_array(char **map, int rows, int cols,
			    point_t const *start, point_t const *target)
{
	queue_t *path, *already_seen;
	queue_node_t *node;
	point_t *start_copy, *valid_point;

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

	valid_point = recursive_call(map, rows, cols, already_seen,
				     path, (point_t *)start, (point_t *)target);
	queue_delete(already_seen);
	if (!valid_point)
	{
		queue_delete(path);
		return (NULL);
	}
	start_copy = malloc(sizeof(point_t));
	if (!start_copy)
		return (NULL);
	start_copy->x = start->x;
	start_copy->y = start->y;
	queue_push_front(path, start_copy);
	return (path);
}
