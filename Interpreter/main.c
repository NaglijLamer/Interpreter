#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "interpreter.h"

int main(int argc, char** argv)
{
	/*//Creating file with byte-code for test.
	FILE* file;
	file = fopen("test", "w");
	fprintf(file, "%c%c%c%c%c%c%c", 0x02, 4, 0x02, 3, 0x0C, 0x16, 0x4C);
	fclose(file);*/
	
	/*//Reading this file and interprete.
	FILE* file;
	function f;
	functions fs;
	file = fopen("test", "r");
	f = (function)malloc(sizeof(char) * 7);
	fs = (functions)malloc(sizeof(function));
	fscanf(file, "%c%c%c%c%c%c%c", f, f+1, f+2, f+3 ,f+4, f+5, f+6);
	fs = (functions)f;
	interpreter(fs, 0, 7);*/
	

	return EXIT_SUCCESS;
}