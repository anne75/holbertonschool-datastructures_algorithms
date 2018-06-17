#include "heap.h"

/**
 * binary_tree_node - create a heap node
 * @parent: parent node of the node to be created
 * @data: data to store in the node
 * Return: pointer to created node or NULL
 */
binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent, void *data)
{
	binary_tree_node_t *new;

	new = malloc(sizeof(binary_tree_node_t));
	if (!new)
		return (NULL);

	new->data = data;
	new->parent = parent;
	new->left = NULL;
	new->right = NULL;
	if (parent)
	{
		if (parent->left == NULL)
		{
			parent->left = new;
		}
		else if (parent->right == NULL)
		{
			parent->right = new;
		}
		else
		{
			free(new);
			new = NULL;
		}
	}
	return (new);
}
