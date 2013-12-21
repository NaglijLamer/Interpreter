
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#define TOTAL 37
#include <stdlib.h>
#include <stdio.h>
#include "interpreter.h"

int main(int argc, char** argv)
{
	/*//Creating file with byte-code for test.
	FILE* file;
	char* ch = (char*)malloc(sizeof(char));
	long long* l = (long long*)malloc(sizeof(long long));
	short* s = (short*)malloc(sizeof(short));
	file = fopen("test", "wb");
	//Program(0x02, (long long)4, 0x02, (long long)3, 0x02, (long long)5, 0x46, (short)4, 0x0E, 0x44, short(1), 0x0C, 0x16, 0x4C)
	*ch = (char)0x02;
	fwrite(ch, sizeof(char), 1, file);
	*l = (long long)4;
	fwrite(l, sizeof(long long), 1, file);
	*ch = (char)0x02;
	fwrite(ch, sizeof(char), 1, file);
	*l = (long long)3;
	fwrite(l, sizeof(long long), 1, file);
	*ch = (char)0x02;
	fwrite(ch, sizeof(char), 1, file);
	*l = (long long)5;
	fwrite(l, sizeof(long long), 1, file);
	*ch = (char)0x46;
	fwrite(ch, sizeof(char), 1, file);
	*s = (short)4;
	fwrite(s, sizeof(short), 1, file);
	*ch = (char)0x0E;
	fwrite(ch, sizeof(char), 1, file);
	*ch = (char)0x44;
	fwrite(ch, sizeof(char), 1, file);
	*s = (short)1;
	fwrite(s, sizeof(short), 1, file);
	*ch = (char)0x0C;
	fwrite(ch, sizeof(char), 1, file);
	*ch = (char)0x16;
	fwrite(ch, sizeof(char), 1, file);
	*ch = (char)0x4C;
	fwrite(ch, sizeof(char), 1, file);
	fclose(file);*/
	
	/*//Reading this file and interprete.
	FILE* file;
	int n;
	function f;
	functions fs;
	file = fopen("test", "rb");
	f = (function)malloc(sizeof(char) * TOTAL);
	fs = (functions)malloc(sizeof(function));
	n = fread(f, sizeof(char), TOTAL, file);
	fclose(file);
	fs = (functions)f;
	interpreter(fs, 0, TOTAL, NULL);*/
	
	return EXIT_SUCCESS;
}