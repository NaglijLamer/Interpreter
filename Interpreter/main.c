
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdlib.h>
#include <stdio.h>
#include "parser.h"

int main(int argc, char** argv)
{	
	//Reading this file and interprete.
	//Test mode.
	FILE* file;
	file = fopen("helloworld", "rb");
	interpreter(parser_file(file));
	
	return EXIT_SUCCESS;
}