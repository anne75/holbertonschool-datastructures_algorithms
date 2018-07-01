#include "huffman.h"

/*
 * this way of doing only works for a linear tree turning to the right, so only
 * one code starts with a 0. Otherwise my idea was to add a 1 to the front and
 * to remove it in the end but in that case, the codes need more than 1 byte
 * to hold in worst case scenario
 */
/**
 * TO REMOVE LATER ON
 * print_binary - print a char in binary format
 * @data: the data that was encoded
 * @c: a char, the code
 */
void print_binary(char data, int c)
{
	char array[9] = {'\0'};
	int i, j;
	char tmp;

	i = 0;
	if (c == 0)
	{
		printf("%c: 0\n", data);
	}
	else
	{
		while (c > 0)
		{
			array[i] = ((c & 1) == 0) ? '0' : '1';
			++i;
			c = c >> 1;
		}
		/*reverse the array*/
		--i;
		array[i--] = 0;
		for (j = 0; j <= i / 2; ++j)
		{
			tmp = array[j];
			array[j] = array[i - j];
			array[i - j] = tmp;
			}
		printf("%c: %s\n", data, array);
	}
}



/**
 * add_match -
 */
int add_match(char data, int code, pair_t **head)
{
	pair_t *new;

	if (!head)
		return (0);

	new = malloc(sizeof(*new));
	if (!new)
		return (0);

	puts("create new match");
	new->data = data;
	new->code = code;
	if (*head)
		new->next = *head;
	else
		new->next = NULL;
	*head = new;
	return (1);
}

/**
 * free_pair -
 */
void free_pair(pair_t *head)
{
	pair_t *tmp;

	while(head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
	return;
}

/**
 * make_codes - build codes from a Huffman tree
 * @tree: a Huffman binary tree
 * @building_char: char used to create the code
 * @head: pointer to linked list holding data/code matches
 * Return: binary_code on success -1 on failure
 */
int make_codes(binary_tree_node_t *tree, int building_char, pair_t **head)
{
	int code, ret;
	char data;

	if (!(tree && head))
	    return (0);

	if (tree->left)
	{
		code = building_char << 1;
		make_codes(tree->left, code, head);
	}
	if (tree->right)
	{
		code = (building_char << 1) | 1;
		make_codes(tree->right, code, head);
	}
	if (!(tree->right || tree->right))
	{
		/*get leaf node symbol data*/
		if (tree->data)
			data = ((symbol_t *)tree->data)->data;
		else
			return (0);
		print_binary(data, building_char);
		ret = add_match(data, building_char, head);
		printf("return add_match: %d\n", ret);
		return (ret);
	}
	return (1);
}


/**
 * huffman_codes - build a huffman tree and print the codes
 * @data: data to compress
 * @freq: frequency of each data point
 * @size: size of data and frequency arrays
 * Return: 1 on success otherwise 0
 */
pair_t *get_codes(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *tree;
	int ret;
	pair_t *head;

	if (!data || !freq || size <= 0)
		return (NULL);
	tree = huffman_tree(data, freq, size);
	if (!tree)
		return (NULL);
	puts("print get codes tree");
	/*binary_tree_print(tree, symbol_print);*/
	head = NULL;
	ret = make_codes(tree, 1, &head);
	printf("return make_codes: %d\n", ret);
/*free binary tree*/
	free_data(tree);
	if (!ret)
	{
		free_pair(head);
		return (NULL);
	}
	return (head);
}
