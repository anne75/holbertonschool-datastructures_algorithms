#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include <stdio.h>
#include <stdlib.h>
#include "heap/heap.h"

/**
 * struct symbol_s - Stores a char and its associated frequency
 *
 * @data: The character
 * @freq: The associated frequency
 */
typedef struct symbol_s
{
	char data;
	size_t freq;
} symbol_t;


/**
 * struct pair_s - Stores a data with its symbol
 *
 * @data: the character
 * @symbol: the associated symbol
 * @next: next data in the linked list
 */
typedef struct pair_s
{
	char data;
	int code;
	struct pair_s *next;
} pair_t;




/*given printing function*/
void binary_tree_print
(const binary_tree_node_t *root, int (*print_data)(char *, void *));

/*questions*/

/*question 5*/
symbol_t *symbol_create(char data, size_t freq);

/*question 6*/
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size);
/*helper function to free a heap which tree nodes contains a tree*/
void free_data(void *p);

/*question 7*/
int huffman_extract_and_insert(heap_t *priority_queue);

/*question 8*/
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size);

/*question 9*/
int huffman_codes(char *data, size_t *freq, size_t size);


/*last question*/
#define ASCII_LENGTH 128

int compress_file(FILE *infile, const char *outfile);
int decompress_file(FILE *infile, const char *outfile);
void fill_weights(FILE *infile, size_t (*weights)[ASCII_LENGTH]);
pair_t *get_codes(char *data, size_t *freq, size_t size);

void print_binary(char data, int c);
int nested_print(char *buffer, void *data);
int symbol_print(char *buffer, void *data);


#endif
