//File with functions that can read file with byte-code. And create a massive from byte-code functions.

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"
#include "parser.h"
#include "instant_exit.h"
#include "constant_pool.h"

//Parser of file.
//The constant '1' in the checking of read proccess must be... seeing better.
registers parser_file(FILE* program)
{
	registers* pointers;
	file_header* fh;
	function_header* mh;
	char *string_buffer, *substring;
	size_t size;
	int current_offset = 0;
	uint i;

	//Reading of file-header.
	fh = (file_header*)malloc(sizeof(file_header));
	size = fread(fh, sizeof(file_header), 1, program);
	if (1 != size || fh->signature != 0x4D56) interpret_crash(wrng_file);

	//Creation of the constant pool.
	pointers = (registers*)malloc(sizeof(registers));
	pointers->pool = pool_create();

	//Reading of constants.
	if (fh->count_constant != 0)
	{
		string_buffer = (char*)malloc(fh->size_of_constant);
		size = fread(string_buffer, sizeof(string_buffer), 1, program);
		if (1 != size) interpret_crash(wrng_file);
		substring = strtok(string_buffer, '\0');
		for (i = 1; i <= fh->count_constant; i++)
		{			
			add_const(i, pointers->pool, substring); 
			if (i < fh->count_constant) substring = strtok(NULL, '\0');
		}
		free(string_buffer);
	}

	//Reading of functions.
	pointers->count_of_functions = fh->count_function;
	pointers->table = (function_table*)malloc(sizeof(function_table) * fh->count_function);
	mh = (function_header*)malloc(sizeof(function_header));
	pointers->byte_code = (function)malloc(fh->size_of_file - fh->size_of_constant - sizeof(file_header) - sizeof(function_header) * fh->count_function);
	for (i = 0; i < fh->count_function; i++)
	{
		size = fread(mh, sizeof(function_header), 1, program);
		if (1 != size) interpret_crash(wrng_file);
		size = fread((pointers->byte_code + current_offset), mh->size_of_byte_code, 1, program);
		if (1 != size) interpret_crash(wrng_file);
		(pointers->table + i)->id = mh->id;
		(pointers->table + i)->offset = pointers->byte_code + current_offset;
		if (mh->id == fh->entry_point_id) pointers->ip = pointers->byte_code + current_offset;
		current_offset += mh->size_of_byte_code;
	}
	free(fh);
	free(mh);
	fclose(program);
	return *pointers;
}