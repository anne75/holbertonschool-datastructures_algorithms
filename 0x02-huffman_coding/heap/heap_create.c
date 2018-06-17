#include "heap.h"

/**
 * heap_create - create a heap data structure
 * @data_cmp: a comparator function to builf the heap
 * Return: pointer to newly created structure or NULL
 */
heap_t *heap_create(int (*data_cmp)(void *, void *))
{
	heap_t *new;

	if (!data_cmp)
		return (NULL);
	new = malloc(sizeof(heap_t));
	if (!new)
		return (NULL);

	new->size = 0;
	new->data_cmp = data_cmp;
	new->root = NULL;

	return (new);
}
