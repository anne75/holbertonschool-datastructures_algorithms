#include "huffman.h"
#include <stdio.h>


/**
 * nested_print - Prints a symbol structure stored in a nested node
 *
 * @buffer: Buffer to print into
 * @data: Pointer to a node's data
 *
 * Return: Number of bytes written in buffer
 */
int nested_print(char *buffer, void *data)
{
	binary_tree_node_t *nested;
	symbol_t *symbol;
	char c;
	int length;

	nested = (binary_tree_node_t *)data;
	symbol = (symbol_t *)nested->data;
	c = symbol->data;
	if (c == -1)
		c = '$';
	length = sprintf(buffer, "(%c[%d]/%lu)", c, c, symbol->freq);
	return (length);
}


/**
 * symbol_print - Prints a symbol structure
 *
 * @buffer: Buffer to print into
 * @data: Pointer to a node's data
 *
 * Return: Number of bytes written in buffer
 */
int symbol_print(char *buffer, void *data)
{
	symbol_t *symbol;
	char c;
	int length;

	symbol = (symbol_t *)data;
	c = symbol->data;
	if (c == -1)
		c = '$';
	length = sprintf(buffer, "(%c/%lu)", c, symbol->freq);
	return (length);
}
