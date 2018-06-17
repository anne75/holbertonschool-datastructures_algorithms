#include "heap.h"

/*prepare level order traversal: queue functions*/
/**
 * free_queue - free a queue
 * @head: head of queue
 */
void free_queue(queue_t **head)
{
	queue_t *tmp;

	if (!head)
		return;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
}

/**
 * enqueue - enqueue an element
 * @head: head of queue
 * @node: node to insert in the end
 * Return: pointer to created node
 */
queue_t *enqueue(queue_t **head, binary_tree_node_t *node)
{
	queue_t *new, *tmp;

	if (!head || !node)
		return (NULL);
	new =  malloc(sizeof(queue_t));
	if (!new)
	{
		free_queue(head);
		return (NULL);
	}
	new->node = node;
	new->next = NULL;
	if (!*head)
	{
		*head = new;
	}
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (new);
}

/**
 * dequeue - pop an element from a queue
 * @queue: pointer to a queue head
 * Return: the value of the popped node
 */
binary_tree_node_t *dequeue(queue_t **queue)
{
	queue_t *first;
	binary_tree_node_t *node;

	if (!queue || !*queue)
		return (NULL);

	first = *queue;
	*queue = first->next;
	node = first->node;
	free(first);
	return (node);
}
