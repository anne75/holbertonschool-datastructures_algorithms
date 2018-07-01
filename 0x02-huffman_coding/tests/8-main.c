#include <stdlib.h>
#include <stdio.h>
#include "heap.h"
#include "huffman.h"

void binary_tree_print(const binary_tree_node_t *heap, int (*print_data)(char *, void *));

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	binary_tree_node_t *root;
	char data[] = {
		'a', 'b', 'c', 'd', 'e', 'f', 'g'
	};
	size_t freq[] = {
		6, 11, 12, 13, 16, 36, 0
	};
	size_t size = sizeof(data) / sizeof(data[0]);

	root = huffman_tree(data, freq, size);
	if (!root)
	{
		fprintf(stderr, "Failed to build Huffman tree\n");
		return (EXIT_FAILURE);
	}
	binary_tree_print(root, symbol_print);

	return (EXIT_SUCCESS);
}
