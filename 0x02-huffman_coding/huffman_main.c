#include "huffman.h"
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int ac, char **av)
{
	FILE *infile;
	int ret_code;

/*check arguments*/
	if (ac != 4)
	{
		puts("Usage: huffman <mode> <filename> <out_filename>");
		exit(EXIT_FAILURE);
	}
/*check outfile does not exist*/
	if (!access(av[3], F_OK))
	{
		printf("File already exists: %s\n", av[3]);
		exit(EXIT_FAILURE);
	}
/*try to open filename*/
	infile = fopen(av[2], "r");
	if (!infile)
	{
		printf("No such file: %s\n", av[2]);
		exit(EXIT_FAILURE);
	}
	if (!strcmp(av[1],"c"))
		ret_code = compress_file(infile, av[3]);
	else if (!strcmp(av[1],"d"))
		puts("no");
/*		ret_code = decompress_file(infile, av[3]);*/
	else
		ret_code = EXIT_FAILURE;
	fclose(infile);
	return (ret_code);
}
