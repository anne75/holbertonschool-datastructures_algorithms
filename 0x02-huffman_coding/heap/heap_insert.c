#include "heap.h"
#include "../huffman.h"
/*
 *	printf("Node1(%p): data(%d) left(%p) right(%p) parent(%p)\n",
 *	       (void *)node1, *((int *)node1->data),
 *	       (void *)node1->left,
 *	       (void *)node1->right, (void *)node1->parent);
 */

/*heapify or percolate up a node in a min heap*/
/**
 * heapify_min - percolate up in a min heap
 * @heap: heap structure
 * @node: node just inserted
 * Return: pointer to the node bearing the newly added data
 */
binary_tree_node_t *heapify_min(heap_t *heap, binary_tree_node_t *node)
{
	binary_tree_node_t *to_return;

	to_return = node;
	while (node->parent)
	{
		if (heap->data_cmp(node->parent->data, node->data) > 0)
		{
			swap_nodes(node, node->parent);
/*to_return = node;*/
		}
node = node->parent;
	}
/*heap->root = node;*/
	return (to_return);
}

/**
 * heap_insert - insert a node in a min heap
 * @heap: pointer to heap structure
 * @data: data to insert in the heap
 * Return: pointer to the created node or NULL
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *new, *node;
	queue_t *queue, *tmp;

	if (!heap)
		return (NULL);
	queue = NULL;
	if (heap->root == NULL)
	{
		new = binary_tree_node(NULL, data);
		if (!new)
			return (NULL);
		heap->root = new;
		heap->size = 1;
		return (new);
	}
	queue = NULL;
	enqueue(&queue, heap->root);
	while (queue)
	{
		node = dequeue(&queue);
		if (node->right)
		{
			enqueue(&queue, node->left);
			enqueue(&queue, node->right);
		}
		else
		{
			while (queue)
			{
				tmp = queue;
				queue = queue->next;
				free(tmp);
			}
		}
	}
	new = binary_tree_node(node, data);
	if (!new)
		return (NULL);
	heap->size += 1;
	return (heapify_min(heap, new));
}
