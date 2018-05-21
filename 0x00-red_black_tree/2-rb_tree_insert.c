#include "rb_trees.h"

#define GRANP(node) ((node)->parent->parent)
#define UNCLE(node) (((GRANP(node))->right == (node->parent)) ?	\
	(GRANP(node))->left : (GRANP(node))->right)

/**
 * rotate_left - left-rotates a tree
 * @tree: ptr to root of tree
 * Return: ptr to new root of tree
 */
rb_tree_t *rotate_left(rb_tree_t *tree)
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
 * rotate_right - rotate a node to the right
 * @node: pointer to a node in a tree
 * Return: pointer to the new parent
 */
rb_tree_t *rotate_right(rb_tree_t *node)
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
 * insert_root - remake tree valid red black
 * @node: node that was inserted
 * @root: root of tree
 * Easy cases
 */
void insert_root(rb_tree_t *node, rb_tree_t **root)
{
	/*first case, node is root, change back color, done*/
	if (!(node->parent))
	{
		node->color = BLACK;
	}
	else
	{
		/*Otherwise, node has a parent*/
		/*second case, parent is black, nothing to do*/
		if ((node->parent)->color == BLACK)
			return;
		insert_red_parent_red_uncle(node, root);
	}
}

/**
 * insert_red_parent_red_uncle - remake tree valid red black
 * @node: node that was inserted
 * @root: root of tree
 * Add a depth of one
 */
void insert_red_parent_red_uncle(rb_tree_t *node, rb_tree_t **root)
{
	rb_tree_t *uncle, *granp;

	/* node has a red parent, that entails node has grandparent*/
	/*
	 * third case uncle is red, increase depth of subtree by one
	 * symmetrically and repeat up
	 */
	uncle = UNCLE(node);
	granp = GRANP(node);
	if (uncle && uncle->color == RED)
	{
		node->parent->color = BLACK;
		uncle->color = BLACK;
		granp->color = RED;
		insert_root(granp, root);
	}
	else
	{
		insert_red_parent_black_uncle(node, root);
	}
}

/**
 * insert_red_parent_black_uncle - remake the tree a valid red black
 * @node: node that was inserted
 * @root: root of tree
 * Rotate to avoid increasing depth
 */
void insert_red_parent_black_uncle(rb_tree_t *node, rb_tree_t **root)
{
	rb_tree_t *granp;

	/*
	 * node has red parent black uncle or none
	 * rotate to avoid increasing depth
	 */
	granp = GRANP(node);
	if ((node == (node->parent)->right) && (node->parent == granp->left))
	{
		node = rotate_left(node->parent);
		node = node->left;
	}
	else if ((node == (node->parent)->left) &&
		 (node->parent == granp->right))
	{
		node = rotate_right(node->parent);
		node = node->right;
	}
	(node->parent)->color = BLACK;
	granp->color = RED;
	if (node == (node->parent)->left)
		node = rotate_right(granp);
	else
		node = rotate_left(granp);
	if (!(node->parent))
		*root = node;
}

/**
 * rb_tree_insert - insert a node in a red black bst
 * @tree: a valid red black bst
 * @value: value to insert
 * Return: pointer to the created node or NULL
 */
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
	rb_tree_t *tmp, *parent, *new;

	if (!*tree)
	{
		*tree = rb_tree_node(*tree, value, BLACK);
		return (*tree);
	}

	tmp = *tree;
	while (tmp)
	{
		parent = tmp;
		if (tmp->n < value)
			tmp = tmp->right;
		else if (tmp->n > value)
			tmp = tmp->left;
		else
			return (NULL);
	}
	new = rb_tree_node(parent, value, RED);
	if (!new)
		return (NULL);
	if (parent->n < value)
		parent->right = new;
	else
		parent->left = new;

	insert_root(new, tree);
	return (new);
}
