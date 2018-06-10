#include "graphs.h"


/**
 * free_vertex - frees a vertex.
 * @vertex: a pointer to a vertex
 */
void free_vertex(vertex_t *vertex)
{
	edge_t *tmp_e;

	if (!vertex)
		return;

	while (vertex->edges)
	{
		tmp_e = vertex->edges;
		vertex->edges = vertex->edges->next;
		free(tmp_e);
		tmp_e = NULL;
	}
	free(vertex->content);
	free(vertex);
}


/**
 * graph_delete - delete all vertices and edges in a graph.
 * @graph: pointer to a graph
 */
void graph_delete(graph_t *graph)
{
	vertex_t *tmp_v1, *tmp_v2;

	if (!graph)
		return;

	tmp_v1 = graph->vertices;
	while (tmp_v1)
	{
		tmp_v2 = tmp_v1;
		tmp_v1 = tmp_v1->next;
		free_vertex(tmp_v2);
		tmp_v2 = NULL;
	}
	graph->vertices = NULL;
	free(graph);
}
