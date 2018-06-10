#include "graphs.h"


/**
 * find_value - find a value stored in a linked list.
 * @l_list: pointer to a linked list
 * @value: string to find
 * Return: pointer to the node holding the value or NULL
 */
vertex_t *find_value(vertex_t *l_list, const char *value)
{
	if (!(l_list && value))
		return (NULL);
	while (l_list)
	{
		if (!strcmp(l_list->content, value))
			break;
		l_list = l_list->next;
	}
	return (l_list);
}

/**
 * vertex_add_edge - add an edge to a vertex
 * @start: a vertex, the source.
 * @dest: destination vertex.
 * Return: pointer to edge on success or NULL;
 */
edge_t *vertex_add_edge(vertex_t *start, vertex_t *dest)
{
	edge_t *new, *tmp;

	if (!(start && dest))
		return (NULL);
	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->dest = dest;
	new->next = NULL;

	tmp = start->edges;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!tmp)
		start->edges = new;
	else
		tmp->next = new;
	++(start->nb_edges);

	return (new);
}


/**
 * graph_add_edge - adds an edge to a graph.
 * @graph: pointer to a graph.
 * @src: value store at the first vertex.
 * @dest: value stored at the second vertex.
 * @type: type of edge (directional or not)
 * Return: 1 on success, 0 on failure.
 */
int graph_add_edge(graph_t *graph, const char *src,
		   const char *dest, edge_type_t type)
{
	edge_t *new, *new_reverse, *tmp;
	vertex_t *start, *end;

	if (!graph || !src || !dest)
		return (0);
	if (!strcmp(src, dest)) /* same node */
		return (0);

	start = find_value(graph->vertices, src);
	if (!start)
		return (0);
	end = find_value(graph->vertices, dest);
	if (!end)
		return (0);

	new = vertex_add_edge(start, end);
	if (!new)
		return (0);
	if (type == BIDIRECTIONAL)
	{
		new_reverse = vertex_add_edge(end, start);
		if (!new_reverse)
		{
			/* remove the first part */
			--start->nb_edges;
			tmp = start->edges;
			if (tmp == new)
				tmp = NULL;
			while (tmp)
			{
				if (tmp->next == new)
					tmp->next = NULL;
				tmp = tmp->next;
			}
			free(new);
			return (0);
		}
	}
	return (1);
}
