#include "rb_trees.h"

/**
 * rb_tree_node - create a node in a red black BST
 * @parent: parent node
 * @value: value of the node
 * @color: color of the node
 * When a node is created it does not have children
 * Return: pointer to the new node or NULL
 */
rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color)
{
	rb_tree_t *new;

	new = malloc(sizeof(rb_tree_t));
	if (!new)
		return (NULL);

	new->parent = parent;
	new->n = value;
	new->color = color;
	new->left = NULL;
	new->right = NULL;
	return (new);
}
