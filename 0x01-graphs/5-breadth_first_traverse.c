#include "graphs.h"


/*define 2 functions to handle a queue (FIFO) for BFS*/

/**
 * insert - insert an element in the queue, at the beginning
 * @queue: pointer to the queue
 * @vertex: vertex to insert in the queue
 * @depth: depth from source node to this one
 * Return: pointer to head of queue on sucess or NULL.
 */
queue_t *insert(queue_t *queue, vertex_t *vertex, size_t depth)
{
	queue_t *new, *tmp;

	if (!vertex)
		return (NULL);

	new = malloc(sizeof(*new));
	if (!new)
	{
		while (queue)
		{
			tmp = queue;
			queue = queue->next;
			free(tmp);
		}
		return (NULL);
	}
	new->vertex = vertex;
	new->next = queue;
	new->depth = depth;
	return (new);
}

/**
 * delete - remove and return the last element from the queue
 * @queue: pointer to head of queue.
 * @depth: hold the depth of the element.
 * Return: the vertex stored at this element.
 */
vertex_t *delete(queue_t **queue, size_t *depth)
{
	queue_t **tmp;
	vertex_t *value;

	if (!(queue && *queue))
		return (NULL);

	tmp = queue;
	while (*tmp && (*tmp)->next)
		tmp = &(*tmp)->next;

	value = (*tmp)->vertex;
	*depth = (*tmp)->depth;
	free(*tmp);
	*tmp = NULL;
	return (value);
}

/**
 * breadth_first_vertex - find largest depth starting at specific vertex.
 * @graph: pointer to graph.
 * @action: pointer to function about vertex.
 * @vertex: source vertex.
 * Return: maximal depth for that vertex in the graph.
 */
size_t breadth_first_vertex(const graph_t *graph,
			    void (*action)(const vertex_t *v, size_t depth),
			    vertex_t *vertex)
{
	edge_t *edges;
	char *in_queue;
	queue_t *queue;
	vertex_t *tmp;
	size_t depth;

	if (!(graph && action && vertex))
		return (0);

	in_queue = calloc(graph->nb_vertices, sizeof(size_t));
	if (!in_queue)
		return (0);
	queue = NULL;
	depth = 0;
	queue = insert(queue, vertex, depth);
	in_queue[vertex->index] = 1;
	if (!queue)
	{
		free(in_queue);
		return (0);
	}
	while (queue)
	{
		tmp = delete(&queue, &depth);
		action(tmp, depth);
		edges = tmp->edges;
		while (edges)
		{
			if (!edges->dest)
				continue;
			if (!in_queue[edges->dest->index])
			{
				queue = insert(queue, edges->dest, depth + 1);
				if (!queue)
				{
					free(in_queue);
					return (0);
				}
				in_queue[edges->dest->index] = 1;
			}
			edges = edges->next;
		}
	}
	free(in_queue);
	return (depth);
}

/**
 * breadth_first_traverse - find largest vertex depth
 * @graph: pointer to a graph
 * @action: pointer to function taking a vertex and a depth.
 * Return: max depth of graph
 */
size_t breadth_first_traverse(const graph_t *graph,
			    void (*action)(const vertex_t *v, size_t depth))
{
	size_t max_depth, tmp_depth;
	vertex_t *vertex;

	if (!(graph && action))
		return (0);

	max_depth = 0;
	vertex = graph->vertices;

	/* while (vertex) */
	/* { */
	tmp_depth = breadth_first_vertex(graph, action, vertex);
	max_depth = MAX(max_depth, tmp_depth);
	/* vertex = vertex->next; */
	/* } */
	return (max_depth);
}
