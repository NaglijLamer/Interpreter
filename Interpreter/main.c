
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdlib.h>
#include <stdio.h>
#include "parser.h"

int main(int argc, char** argv)
{
	/*//Creating file with byte-code for test.
	FILE* file;
	ushort* us = (ushort*)malloc(sizeof(ushort));
	uint* ui = (uint*)malloc(sizeof(uint));
	char* ch = (char*)malloc(sizeof(char));
	long long* l = (long long*)malloc(sizeof(long long));
	short* s = (short*)malloc(sizeof(short));
	file = fopen("test", "wb");
	
	*us = (ushort)0x4D56;
	fwrite(us, sizeof(ushort), 1, file);
	*us = (ushort)1;
	fwrite(us, sizeof(ushort), 1, file);
	*ui = (uint)0;
	fwrite(ui, sizeof(uint), 1, file);
	*ui = (uint)0;
	fwrite(ui, sizeof(uint), 1, file);
	*ui = (uint)73;
	fwrite(ui, sizeof(uint), 1, file);
	*us = (ushort)2;
	fwrite(us, sizeof(ushort), 1, file);
	*ui = (uint)1;
	fwrite(ui, sizeof(uint), 1, file);

	*us = (ushort)2;
	fwrite(us, sizeof(ushort), 1, file);
	*ui = (uint)51;
	fwrite(ui, sizeof(uint), 1, file);
	*ui = (uint)37;
	fwrite(ui, sizeof(uint), 1, file);
	*us = (ushort)0;
	fwrite(us, sizeof(ushort), 1, file);
	*us = (ushort)0;
	fwrite(us, sizeof(ushort), 1, file);

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
	file = fopen("test", "rb");
	interpreter(parser_file(file));*/
	
	return EXIT_SUCCESS;
}