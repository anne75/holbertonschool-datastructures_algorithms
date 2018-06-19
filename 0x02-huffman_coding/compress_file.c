#include "huffman.h"


int compress_file(FILE *infile, const char *outfile)
{

/*need one array of weights, an index doubles as ascii value*/
	size_t weigths[ASCII_LENGTH] = {0};
	char ascii[ASCII_LENGTH];
	/*pair_t *pairs;*/
	int i;
	(void ) outfile;

	fill_weights(infile, &weigths);

/* I need to adapt with what I have done before :(*/
	for (i = 0; i < ASCII_LENGTH; ++i)
		ascii[i] = i;

	for (i = 0; i < ASCII_LENGTH; ++i)
	{
		printf("%c -> %lu\n", ascii[i], weigths[i]);
	}
	return (1);
/* call the huffman encoding */
/*	pairs = get_codes(ascii, weights, 128);*/
}


void fill_weights(FILE *infile, size_t (*weights)[ASCII_LENGTH])
{
	char *line_buffer;
	size_t buf_length;
	ssize_t read_length, i;

	line_buffer = NULL;
	buf_length = 0;
	while ((read_length = getline(&line_buffer, &buf_length, infile)) != -1)
	{
		for (i = 0; i < read_length; ++i)
		{
			++(*weights)[(unsigned char) line_buffer[i]];
		}
		free(line_buffer);
		line_buffer = NULL;
	}
	return;
}
