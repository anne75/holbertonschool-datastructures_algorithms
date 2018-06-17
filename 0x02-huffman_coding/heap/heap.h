#ifndef _HEAP_H_
#define _HEAP_H_

#include <stdlib.h>
#include <stdio.h>

/* structs */
/**
 * struct binary_tree_node_s - Binary tree node data structure
 *
 * @data: Data stored in a node
 * @left: Pointer to the left child
 * @right: Pointer to the right child
 * @parent: Pointer to the parent node
 */
typedef struct binary_tree_node_s
{
	void *data;
	struct binary_tree_node_s *left;
	struct binary_tree_node_s *right;
	struct binary_tree_node_s *parent;
} binary_tree_node_t;

/**
 * struct heap_s - Heap data structure
 *
 * @size: Size of the heap (number of nodes)
 * @data_cmp: Function to compare two nodes data
 * @root: Pointer to the root node of the heap
 */
typedef struct heap_s
{
	size_t size;
	int (*data_cmp)(void *, void *);
	binary_tree_node_t *root;
} heap_t;

/**
 * struct queue_s - Queue data structure
 * @node: binary tree node
 * @next: pointer to next queue node
 */
typedef struct queue_s
{
	binary_tree_node_t *node;
	struct queue_s *next;
} queue_t;


/* prototypes */

/*given printing function*/
void binary_tree_print
(const binary_tree_node_t *root, int (*print_data)(char *, void *));

/*queue related functions*/
void free_queue(queue_t **head);
queue_t *enqueue(queue_t **head, binary_tree_node_t *node);
binary_tree_node_t *dequeue(queue_t **queue);

/*helpers to swap node*/
void swap_node_pointers(binary_tree_node_t *child, binary_tree_node_t *parent);
void swap_nodes(binary_tree_node_t *node1, binary_tree_node_t *node2);

/*question 0*/
heap_t *heap_create(int (*data_cmp)(void *, void *));

/*question 1*/
binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent, void *data);

/*question 2*/
binary_tree_node_t *heap_insert(heap_t *heap, void *data);

/*question 3*/
void *heap_extract(heap_t *heap);

/*question 4*/
void heap_delete(heap_t *heap, void (*free_data)(void *));

#endif
