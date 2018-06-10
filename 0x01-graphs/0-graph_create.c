#include "graphs.h"

/**
 * graph_create - allocate memory to store a graph.
 *
 * Return: pointer to the allocated strcuture or NULL.
 */
graph_t *graph_create(void)
{
	graph_t *graph;

	graph = malloc(sizeof(graph_t));
	if (!graph)
		return (NULL);
	graph->nb_vertices = 0;
	graph->vertices = NULL;
	return (graph);
}
