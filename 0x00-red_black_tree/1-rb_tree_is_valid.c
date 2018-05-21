#include "rb_trees.h"

#define MAX(X, Y) (((X) >= (Y)) ? (X) : (Y))

/**
 * is_bst - check if a binary tree is a binary search tree
 * @tree: a binary tree
 * @min: node bearing the minimum value a node can have
 * @max: node bearing the maximum value a node can have
 * Return: 1 if true, 0 if false
 */
int is_bst(const rb_tree_t *tree, const rb_tree_t *min, const rb_tree_t *max)
{
	if (!tree)
		return (1);
	if (min && tree->n < min->n)
		return (0);
	if (max && tree->n > max->n)
		return (0);
	return (is_bst(tree->left, NULL, tree) &&
		is_bst(tree->right, tree, NULL));
}

/**
 * is_right_colors - check if all nodes have right colors and no adjacent
 * red nodes
 * @tree: a binary tree
 * Return: 1 if true, 0 of false
 */
int is_right_colors(const rb_tree_t *tree)
{
	if (!tree)
		return (1);
	if (!((tree->color == RED) || (tree->color == BLACK)))
		return (0);
	if (tree->color == RED)
	{
		if (tree->left)
			if ((tree->left)->color == RED)
				return (0);
		if (tree->right)
			if ((tree->right)->color == RED)
				return (0);
	}
	return (is_right_colors(tree->left) &&
		is_right_colors(tree->right));
}

/**
 * black_height - returns the black height of a rbbst
 * @tree: a red black bst
 * Return: the max number of black nodes between the root and leaf nodes
 */
size_t black_height(const rb_tree_t *tree)
{
	size_t max;

	if (!tree)
		return (0);
	max = MAX(black_height(tree->left), black_height(tree->right));
	if (tree->color == BLACK)
		return (max + 1);
	return (max);
}

/**
 * is_path_constant - check the black height is the same throughout
 * @tree: a red black bst
 * @height: black height of the tree
 * @count: count of black nodes so far
 * Return: 1 if true, 0 if false
 */
int is_path_constant(const rb_tree_t *tree, size_t height, size_t count)
{
	if (!tree)
	{
		if (height == count)
			return (1);
		return (0);
	}
	if (tree->color == BLACK)
		++count;
	return (is_path_constant(tree->left, height, count) &&
		is_path_constant(tree->right, height, count));
}

/**
 * rb_tree_is_valid - check if a binary tree is a rb tree
 * @tree: a binary tree
 * A rb tree is valid if:
 * - the root is black
 * - every node is either red or black
 * - there are no 2 adjacent red nodes
 * - every path from root to NULL as same number of black nodes
 * Return: 1 if true, 0 if false or NULL
 */
int rb_tree_is_valid(const rb_tree_t *tree)
{
	size_t h;

	if (!tree)
		return (0);
	if (tree->color != BLACK)
		return (0);
	if (!is_bst(tree, NULL, NULL))
		return (0);
	if (!is_right_colors(tree))
		return (0);
	h = black_height(tree);
	if (!is_path_constant(tree, h, 0))
		return (0);
	return (1);
}
