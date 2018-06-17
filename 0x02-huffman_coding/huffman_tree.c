#include "huffman.h"

/**
 * huffman_tree - build a huffman tree from 2 arrays of chars and frequency
 * @data: array of chars
 * @freq: frequencies of each char
 * @size: size of arrays
 * Return: a huffman tree
 */
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *root;
	heap_t *heap;
	int result;

	heap = huffman_priority_queue(data, freq, size);
	if (!heap)
		return (NULL);

	while (heap->size > 1)
	{
		result = huffman_extract_and_insert(heap);
		if (result == 0)
			break;
	}
	root = (binary_tree_node_t *)heap_extract(heap);
	heap_delete(heap, free_data);
	return (root);
}
