#include "rb_trees.h"

/**
 * array_to_rb_tree - build a red black tree from an array
 * @array: array of values to insert
 * @size: size of array
 * Return: root of the tree
 */
rb_tree_t *array_to_rb_tree(int *array, size_t size)
{
	size_t i;
	rb_tree_t *root;

	root = NULL;
	for (i = 0; i < size; ++i)
	{
		rb_tree_insert(&root, array[i]);
	}
	return (root);
}
