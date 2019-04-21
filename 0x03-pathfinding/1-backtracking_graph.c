#include <string.h>

#include "pathfinding.h"


/**
 * vertex_is_new - checks we have never been there before.
 * @to_check: content of vertex to check
 * @already_seen: queue of vertex's content already visited
 * Return: 0 if already visited 1 otherwise.
 */
int vertex_is_new(char *to_check, queue_t *already_seen)
{
	queue_node_t *front;
	char *value;

	if (!(to_check && already_seen))
		return (0);

	front = already_seen->front;
	while (front)
	{
		value = (char *)front->ptr;
		if (strcmp(value, to_check) == 0)
			return (0);
		front = front->next;
	}
	return (1);
}

/**
 * recursive_call - batcktracking recursive function
 * @graph: graph of cities to visit.
 * @start: starting vertex.
 * @target: end vertex.
 * @already_seen: queue of already seen vertexes (only the cities name).
 * @path: queue of cities to visit to go fram start to target.
 * Return: 1 if there is a path, 0 otherwise.
 */
int recursive_call(graph_t *graph, vertex_t const *start,
		   vertex_t const *target, queue_t *already_seen, queue_t *path)
{
	char *tmp_value;
	edge_t *start_edge;
	int success;
	queue_node_t *node;
	vertex_t *destination;

	if (!(graph && start && start->content && target && target->content))
		return (0);
	printf("Checking %s\n", start->content);
	if (strcmp(start->content, target->content) == 0)
		return (1);
	start_edge = start->edges;
	while (start_edge)
	{
		destination = start_edge->dest;
		if (vertex_is_new(destination->content, already_seen))
		{
			node = queue_push_front(already_seen,
						destination->content);
			if (!node)
				return (0);
			success = recursive_call(graph, destination, target,
						 already_seen, path);
			if (success)
			{
				tmp_value = strdup(destination->content);
				if (!tmp_value)
					return (0);
				node = queue_push_front(path, tmp_value);
				if (!node)
				{
					free(tmp_value);
					return (0);
				}
				return (success);
			}
		}
		start_edge = start_edge->next;
	}
	return (0);
}

/**
 * delete_path - delete/free a queue and its content.
 * @path: queue of strings to free.
 */
void delete_path(queue_t *path)
{
	char *content;

	while (path->front)
	{
		content = (char *)dequeue(path);
		free(content);
	}
	free(path);
}

/**
 * backtracking_graph - bactracking algorithm entrypoint.
 * @graph: graph on which to operate.
 * @start: vertex/city to start from.
 * @target: vertex/city to end to.
 * Return: on success the path from start to target, NULL otherwise.
 */
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
			    vertex_t const *target)
{
	int success;
	char *content_copy;
	queue_node_t *node;
	queue_t *path, *already_seen;

	if (!(graph && graph->vertices && start && start->content &&
	      target && target->content))
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
	node = queue_push_front(already_seen, start->content);
	if (!node)
	{
		queue_delete(path), queue_delete(already_seen);
		return (NULL);
	}
	/* should I check a vertex is in the graph? */
	success = recursive_call(graph, start, target, already_seen, path);
	queue_delete(already_seen);
	if (success)
	{
		content_copy = strdup(start->content);
		if (!content_copy)
			delete_path(path), path = NULL;
		node = queue_push_front(path, content_copy);
		if (!node)
			free(content_copy), delete_path(path), path = NULL;
	}
	else
	{
		delete_path(path), path = NULL;
	}
	return (path);
}
