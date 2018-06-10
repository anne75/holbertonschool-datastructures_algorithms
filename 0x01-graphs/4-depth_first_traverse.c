#include "graphs.h"


/**
 * depth_first_vertex - find largest depth starting at specific vertex.
 * @graph: pointer to graph.
 * @action: pointer to function about vertex.
 * @vertex: source vertex;
 * @visited: array indicating already visited vertices.
 * @depth: Distance from source node.
 * Return: maximal depth for that vertex in the graph.
 */
size_t depth_first_vertex(const graph_t *graph,
			  void (*action)(const vertex_t *v, size_t depth),
			  vertex_t *vertex, char *visited, size_t depth)
{
	size_t max_depth, tmp_depth;
	edge_t *edges;

	if (!(graph && action && vertex && visited))
		return (0);

	max_depth = depth;
	edges = vertex->edges;
	visited[vertex->index] = 1;
	action(vertex, depth);
	/* loop through the edges, get the max depth for each vertex */
	while (edges)
	{
		if (!edges->dest)
			break;
		if (!visited[edges->dest->index])
		{
			tmp_depth = depth_first_vertex(graph, action,
						       edges->dest,
						       visited,
						       depth + 1);
			/* adjust the max depth found so far */
			max_depth = MAX(max_depth, tmp_depth);
		}
		edges = edges->next;
	}
	return (max_depth);
}

/**
 * depth_first_traverse - find largest vertex depth
 * @graph: pointer to a graph
 * @action: pointer to function taking a vertex and a depth.
 * Return: max depth of graph
 */
size_t depth_first_traverse(const graph_t *graph,
			    void (*action)(const vertex_t *v, size_t depth))
{
	size_t max_depth, tmp_depth;
	vertex_t *vertex;
	char *visited;

	if (!(graph && action))
		return (0);

	max_depth = 0;
	vertex = graph->vertices;
	/* array of index 0 if this vertex has not been visited or 1 */
	visited = malloc(graph->nb_vertices);
	if (!visited)
		return (0);

	/* while (vertex) */
	/* { */
	memset(visited, 0, graph->nb_vertices);
	tmp_depth = depth_first_vertex(graph, action, vertex, visited, 0);
	max_depth = MAX(max_depth, tmp_depth);
	/* vertex = vertex->next; */
	/* } */
	free(visited);
	return (max_depth);
}
