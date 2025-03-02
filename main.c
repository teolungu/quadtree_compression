/* LUNGU Mihai-Teodor - 313CD */

#include <stdio.h>
#include <string.h>
#include "headers.h"

FILE *input;
FILE *output;

int main(int argc, char *argv[])
{
	if(strcmp("-c1", argv[1]) == 0){
		input = fopen(argv[3], "rb");

		Image *image = readppm(input);

		unsigned long long prag = atoi(argv[2]);
		Tree root = compression(image, NULL, 0, 0, image->size, prag);

		output = fopen(argv[4], "wb");
		fprintf(output, "%llu\n", height(root));
		fprintf(output, "%llu\n", leaf_number(root));
		fprintf(output, "%llu\n", largest(image, 0, 0, image->size, prag));
	}

	return 0;
}