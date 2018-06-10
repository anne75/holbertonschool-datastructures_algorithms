#include <stdlib.h>
#include <stdio.h>
#include "../rb_trees.h"

/* TODO: This test is identical to main_1 */

void rb_tree_print(const rb_tree_t *tree);
void rb_tree_delete(rb_tree_t *tree);
/* rb_tree_t *array_to_rb_tree(int *array, size_t size);*/

/**
 * main - Entry point
 *
 * Return: 0 on success, error code on failure
 */
int main(void)
{
	rb_tree_t *tree;
	int array[] = {
		79, 47, 68, 87, 84, 91, 21, 32, 34, 2,
		20, 22
	};
	size_t n = sizeof(array) / sizeof(array[0]);

	tree = array_to_rb_tree(array, n);
	if (!tree)
	{
		printf("Failed to create RB tree from array\n");
		return (EXIT_FAILURE);
	}
	rb_tree_print(tree);

	puts("remove 32");
	rb_tree_remove(tree,32);
	rb_tree_print(tree);

	/* rb_tree_delete(tree); */
	return (EXIT_SUCCESS);
}
