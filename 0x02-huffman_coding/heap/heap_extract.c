#include "heap.h"
#include "../huffman.h"
/**
 * heapify_down - dive the root to its normal place
 * @heap: heap struct
 * if a node has one child it is a left child as a heap is complete
 * beware with cmp, node->data can be a binary_tree_node, so the function
 * will have to go deeper
 */
void heapify_down(heap_t *heap)
{
	binary_tree_node_t *node;

	if (!heap || !heap->root || !(heap->root)->left)
		return;

	node = heap->root;
	while (node->left)
	{
		if (node->right &&
		    heap->data_cmp(node->right->data,
				   node->left->data) < 0 &&
		    heap->data_cmp(node->data,
				   node->right->data) >= 0)
		{
			swap_nodes(node->right, node);
			node = node->right;
			continue;
		}
		else if (heap->data_cmp(node->left->data,
					node->data) <= 0)
		{
			swap_nodes(node->left, node);
		}
		node = node->left;
	}
}

/**
 * heap_extract - extract the first element of a heap
 * @heap: heap struct
 * Return: data element of the extracted heap node
 */
void *heap_extract(heap_t *heap)
{
	queue_t *queue;
	binary_tree_node_t *node;
	void *data;

	if (!heap)
		return (NULL);
	if (!(heap->root))
		return (NULL);
	queue = NULL;
	enqueue(&queue, heap->root);
	while (queue)
	{
		node = dequeue(&queue);
		enqueue(&queue, node->left);
		enqueue(&queue, node->right);
	}
	data = (heap->root)->data;
	if (node == heap->root)
	{
		free(node);
		heap->root = NULL, heap->size = 0;
		return (data);
	}

	if ((node->parent)->left == node)
		(node->parent)->left = NULL;
	else
		(node->parent)->right = NULL;
/*prepare swapping with the root, as we remove the root*/
	swap_nodes(heap->root, node);
	free(node);
	heap->size -= 1;
	heapify_down(heap);
	return (data);
}

/*
 *printf("value %c %lu\n",
 *((symbol_t *)((binary_tree_node_t *)
 *(node->data))->data)->data,
 *((symbol_t *)((binary_tree_node_t *)(node->data))
 *->data)->freq);
 */
