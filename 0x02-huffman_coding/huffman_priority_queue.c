#include "huffman.h"

/**
 * freq_cmp - compare the frequencies of 2 symbol_t
 * @v1: first symbol
 * @v2: second symbol
 * This function belongs to the heap. It works if the heap
 * stores binary_tree_nodes which themselves store symbol_t
 *
 * Return: difference in frequency
 */
int freq_cmp(void *v1, void *v2)
{
	binary_tree_node_t *n1, *n2;
	symbol_t *s1, *s2;

	if (!v1 || !v2)
		return (-666);

	n1 = (binary_tree_node_t *)v1;
	n2 = (binary_tree_node_t *)v2;
	s1 = (symbol_t *)(n1->data);
	s2 = (symbol_t *)(n2->data);
	return (s1->freq - s2->freq);
}

/**
 * free_data - frees a node in a heap
 * @p: should be a binary_tree_node
 * Free a tree of binary_tree_node containing symbol values
 */
void free_data(void *p)
{
	binary_tree_node_t *tmp;

	if (!p)
		return;
	tmp = (binary_tree_node_t *)p;

	free_data((void *)tmp->left);
	free_data((void *)tmp->right);
	if (tmp->data)
		free(tmp->data);
	free(tmp);
}

/**
 * huffman_priority_queue - create a min heap with arrays of data and freq
 * @data: data to store in a priority queue
 * @freq: frequency associated with each data
 * @size: size of data and freq arrays
 * Return: pointer to the created min heap or NULL
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	size_t i;
	heap_t *heap;
	symbol_t *new;
	binary_tree_node_t *node;

	if (!data || !freq || size <= 0)
		return (NULL);

	heap = heap_create(freq_cmp);
	if (!heap)
		return (NULL);
	for (i = 0; i < size; ++i)
	{
		new = symbol_create(data[i], freq[i]);
		if (!new)
		{
			heap_delete(heap, free_data);
			return (NULL);
		}
		node = binary_tree_node(NULL, (void *)new);
		if (!node)
		{
			free(new);
			heap_delete(heap, free_data);
			return (NULL);
		}
		heap_insert(heap, (void *)node);
	}
	return (heap);
}
