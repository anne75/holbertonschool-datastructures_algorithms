CC = gcc-4.8
CFLAGS = -Wall -Wextra -Werror -pedantic
HEAP = heap/


huffman:
	$(CC) $(CFLAGS) -I$(HEAP) -I./ $(HEAP)/*.c symbol.c huffman_priority_queue.c huffman_extract_and_insert.c huffman_tree.c get_codes.c binary_tree_print.c compress_file.c huffman_main.c -o huffman
