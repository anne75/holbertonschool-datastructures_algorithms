#include "heap.h"

/**
 * swap_nodes - swap 2 nodes values
 * @node1: node to swap
 * @node2: node to swap
 */
void swap_nodes(binary_tree_node_t *node1, binary_tree_node_t *node2)
{
	void *tmp;

	tmp = node1->data;
	node1->data = node2->data;
	node2->data = tmp;
}
