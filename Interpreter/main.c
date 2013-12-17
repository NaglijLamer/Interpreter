#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "interpreter.h"

int main(int argc, char** argv)
{
	/*//Creating file with byte-code for test.
	FILE* file;
	char* ch = (char*)malloc(sizeof(char));
	long long* l = (long long*)malloc(sizeof(long long));
	file = fopen("test", "wb");
	//fread(0x02, (long long)4, 0x02, (long long)3, 0x0C, 0x16, 0x4C);
	*ch = (char)0x02;
	fwrite(ch, sizeof(char), 1, file);
	*l = (long long)4;
	fwrite(l, sizeof(long long), 1, file);
	*ch = (char)0x02;
	fwrite(ch, sizeof(char), 1, file);
	*l = (long long)3;
	fwrite(l, sizeof(long long), 1, file);
	*ch = (char)0x0C;
	fwrite(ch, sizeof(char), 1, file);
	*ch = (char)0x16;
	fwrite(ch, sizeof(char), 1, file);
	*ch = (char)0x4C;
	fwrite(ch, sizeof(char), 1, file);
	fclose(file);*/
	
	//Reading this file and interprete.
	FILE* file;
	int n;
	function f;
	functions fs;
	file = fopen("test", "rb");
	f = (function)malloc(sizeof(char) * 21);
	fs = (functions)malloc(sizeof(function));
	n = fread(f, sizeof(char), 21, file);
	fclose(file);
	fs = (functions)f;
	interpreter(fs, 0, 21);
	

	return EXIT_SUCCESS;
}