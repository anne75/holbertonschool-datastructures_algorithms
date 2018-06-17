#include "huffman.h"

/**
 * symbol_create - create a symbol_t data type
 * @data: data to store in the structure
 * @freq: associated frequency
 * Return: a pointer to the new strcuture or NULL
 */
symbol_t *symbol_create(char data, size_t freq)
{
	symbol_t *new;

	new = malloc(sizeof(symbol_t));
	if (!new)
		return (NULL);

	new->data = data;
	new->freq = freq;
	return (new);
}
