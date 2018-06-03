#include <stdlib.h>
#include "../rb_trees.h"

void rb_tree_print(const rb_tree_t *tree);

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
	/* int array[] = {1} */
	size_t n = sizeof(array) / sizeof(array[0]);

	tree = array_to_rb_tree(array, n);
	if (!tree)
		return (1);
	rb_tree_print(tree);

	puts("Remove 32");
	tree = rb_tree_remove(tree, 32);
	rb_tree_print(tree);

	puts("Remove 84");
	tree = rb_tree_remove(tree, 84);
	rb_tree_print(tree);

	puts("Remove 34");
	tree = rb_tree_remove(tree, 34);
	rb_tree_print(tree);

	puts("Remove 68");
	tree = rb_tree_remove(tree, 68);
	rb_tree_print(tree);

	return (0);
}
