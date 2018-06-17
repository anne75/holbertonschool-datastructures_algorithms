#include "huffman.h"


int compress_file(FILE infile, const char *outfile)
{

/*need one array of weights, an index doubles as ascii value*/
	size_t weigths[128];
	char ascii[128], i;

	weights = {0};

	fill_weights(infile, &weights);

/* I need to adapt with what I have done before :(*/
	for (i = 0, i < sizeof(ascii); ++i)
		ascii[i] = i;

/* call the huffman encoding */

}
