#include "rb_trees.h"

/* rotations must be redifined here for correction */

/**
 * rb_rotate_left - left-rotates a rb tree
 * @tree: ptr to root of tree
 * Return: ptr to new root of tree
 */
rb_tree_t *rb_rotate_left(rb_tree_t *tree)
{
	rb_tree_t *temp;

	if (!tree)
		return (NULL);
	temp = tree->right;
	if (!temp)
		return (tree);
	tree->right = (temp)->left;
	if (temp->left)
		temp->left->parent = tree;
	temp->parent = tree->parent;
	if (tree->parent)
	{
		if (tree == tree->parent->left)
			tree->parent->left = temp;
		else
			tree->parent->right = temp;
	}
	temp->left = tree;
	tree->parent = temp;
	return (temp);
}


/**
 * rb_rotate_right - rotate a node to the right
 * @node: pointer to a node in a rb tree
 * Return: pointer to the new parent
 */
rb_tree_t *rb_rotate_right(rb_tree_t *node)
{
	rb_tree_t *tmp;

	if (!node)
		return (NULL);
	tmp = node->left;

	if (!tmp)
		return (node);

	node->left = tmp->right;
	if (node->left)
		(node->left)->parent = node;

	tmp->right = node;
	tmp->parent = node->parent;
	if (tmp->parent)
	{
		if ((tmp->parent)->left == node)
			(tmp->parent)->left = tmp;
		else
			(tmp->parent)->right = tmp;
	}
	node->parent = tmp;

	return (tmp);
}


/**
 * delete_min - delete the minimum node in a rb search tree
 * @tree: pointer to root
 * Return: the minimum node
 */
rb_tree_t *delete_min(rb_tree_t *tree)
{

	if (!tree)
		return (NULL);
	while (tree->left)
		tree = tree->left;
	return (tree);
}


/**
 * right_sibling - the node to remove is the left child.
 * @parent: parent of the nodes
 * @root: root of tree
 * Return: node on which to loop (or not)
 */
rb_tree_t *right_sibling(rb_tree_t *parent, rb_tree_t **root)
{
	rb_tree_t *sibling, *removed;

	sibling = parent->right;
	removed = parent->left;
	if (!sibling)
		return (NULL);

	if (sibling->color == BLACK)
	{
		if ((!sibling->right || sibling->right->color == BLACK) &&
		    sibling->left && sibling->left->color == RED)
		{
			parent->right = rb_rotate_right(sibling);
			sibling = parent->right;
			sibling->color = BLACK, sibling->right->color = RED;
		}
		if (sibling->right && sibling->right->color == RED)
			/*sibling has right red child*/
		{
			if (!parent->parent)
				*root = rb_rotate_left(parent);
			else
			{
				rb_rotate_left(parent);
			}
			sibling->right->color = BLACK;
			removed->color = BLACK;
			sibling->color = parent->color;
			parent->color = BLACK;
			return (removed);
		}
		else  /*sibling black, only black children*/
		{
			sibling->color = RED;
			if (parent->color == RED)
				parent->color = BLACK;
			else
				parent->color = DOUBLE_BLACK;
			return (parent);
		}
	}
	else /* sibling->color == RED, rotate to have a black sibling */
	{
		if (!parent->parent)
			*root = rb_rotate_left(parent);
		else
		{
			rb_rotate_left(parent);
		}
		sibling->color = BLACK;
		parent->color = RED;
	}
	return (removed);
}


/**
 * left_sibling - the node to remove is the right child.
 * @parent: parent of the nodes
 * @root: root of tree
 * Return: node on which to loop (or not)
 */
rb_tree_t *left_sibling(rb_tree_t *parent, rb_tree_t **root)
{
	rb_tree_t *sibling, *removed;

	sibling = parent->left;
	removed = parent->right;
	if (!sibling)
		return (NULL);

	if (sibling->color == BLACK)
	{
		if ((!sibling->left || sibling->left->color == BLACK) &&
		    sibling->right && sibling->right->color == RED)
		{
			parent->left = rb_rotate_left(sibling);
			sibling = parent->left;
			sibling->color = BLACK, sibling->left->color = RED;
		}
		if (sibling->left && sibling->left->color == RED)
			/*sibling has left red child*/
		{
			if (!parent->parent)
				*root = rb_rotate_right(parent);
			else
			{
				rb_rotate_right(parent);
			}
			removed->color = BLACK;
			sibling->left->color = BLACK;
			sibling->color = parent->color;
			parent->color = BLACK;
			return (removed);
		}
		else
		{
			sibling->color = RED;
			if (parent->color == RED)
				parent->color = BLACK;
			else
				parent->color = DOUBLE_BLACK;
			return (parent);
		}
	}
	else /* sibling->color == RED */
	{
		if (!parent->parent)
			*root = rb_rotate_right(parent);
		else
		{
			rb_rotate_right(parent);
		}
		sibling->color = BLACK;
		parent->color = RED;
	}
	return (removed);
}


/**
 * re_bst - make the tree a valid red black tree after deletion
 * @root: root of the tree
 * @removed: removed node, has at most one child that is not a leaf
 * Return: the root of the tree
 */
rb_tree_t *re_bst(rb_tree_t *root, rb_tree_t *removed)
{
	rb_tree_t *child, *parent, *to_free;

	if (!root || !removed)
		return (removed);
	/*Removed->color == RED, it must be terminal node (2 leafs)*/
	if (removed->color == RED)
	{
		if (removed->parent->right == removed)
			removed->parent->right = NULL;
		else
			removed->parent->left = NULL;
		free(removed);
		return (root);
	}
	/*removed->color == BLACK*/
	child = (removed->left == NULL) ? removed->right : removed->left;
	if (child && child->color == RED)
	{
		removed->n = child->n;
		if (child == removed->left)
			removed->left = NULL;
		else
			removed->right = NULL;
		free(child);
		return (root);
	}
	to_free = removed, removed->color = DOUBLE_BLACK;
	/*removed has 2 NULL children, NULL children are black*/
	while ((parent = removed->parent) && removed->color == DOUBLE_BLACK)
	{
		if (parent->left == removed)
		{
			removed = right_sibling(parent, &root);
		}
		else
		{
			removed = left_sibling(parent, &root);
		}
	}
	if (to_free->parent)
	{
		if (to_free->parent->left == to_free)
			to_free->parent->left = NULL;
		else
			to_free->parent->right = NULL;
	}
	free(to_free);
	return ((to_free == root) ? NULL : root);
}

/**
 * rb_tree_remove - remove a node from a rb bst
 * @root: root of the tree
 * @value: value to remove
 * Return: root of the tree
 */
rb_tree_t *rb_tree_remove(rb_tree_t *root, int value)
{
	rb_tree_t *tmp, *removed;

	if (!root)
		return (NULL);
	tmp = root;
	while (tmp)
	{
		if (tmp->n < value)
			tmp = tmp->right;
		else if (tmp->n > value)
			tmp = tmp->left;
		else
			break;
	}
	if (!tmp)
		return (root);
	if ((tmp->right) && (tmp->left))
	{
		removed = delete_min(tmp->right);
		tmp->n = removed->n;
		root = re_bst(root, removed);
	}
	else
	{
		root = re_bst(root, tmp);
	}
	if (root)
		root->color = BLACK;
	return (root);
}
