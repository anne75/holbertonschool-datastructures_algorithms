#include "huffman.h"


#include <fcntl.h>

int main(int ac, char **av)
{
	FILE infile;
	int ret_code;

/*check arguments*/
	if (ac != 4)
	{
		puts("Usage: huffman <mode> <filename> <out_filename>");
		exit(EXIT_FAILURE);
	}
/*check outfile does not exist*/
	if (!access(ac[3], F_OK))
	{
		printf("File already exists: %s\n", ac[3]);
		exit(EXIT_FAILURE);
	}
/*try to open filename*/
	infile = fopen(ac[2], "r");
	if (infile <= 0)
	{
		printf("No such file: %s\n", ac[2]);
	}
	if (ac[1] == "c")
		ret_code = compress(infile, ac[3]);
	else if (ac[1] == "d")
		ret_code = decompress(infilde, ac[3]);
	else
		ret_code = EXIT_FAILURE;
	fclose(infile);
	return (ret_code);
}
