
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdlib.h>
#include <stdio.h>
#include "parser.h"

int main(int argc, char** argv)
{	
	//Reading this file and interprete.
	FILE* file;
#ifdef _DEBUG
	file = fopen("outp", "rb");
#else
	if (argc != 2) program_crash(usage);
	if ((file = fopen(argv[1], "rb")) == NULL) program_crash(wrng_fname);
#endif
	interpreter(parser_file(file));
	return EXIT_SUCCESS;
}