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
//In the future we must create some registers for count of locals or arguments. Or. Add this information to the table of functions.
registers parser_file(FILE* program)
{
	registers* pointers;
	file_header1* fh1;
	file_header2* fh2;
	function_header1* mh1;
	function_header2* mh2;
	char *string_buffer, *substring;
	size_t size;
	int current_offset = 0;
	uint i;

	//Reading of the first part of file-header.
	fh1 = (file_header1*)malloc(sizeof(file_header1));
	size = fread(fh1, sizeof(file_header1), 1, program);
	if (1 != size || fh1->signature != 0x4D56) interpret_crash(wrng_file);

	//Creation of the constant pool.
	pointers = (registers*)malloc(sizeof(registers));
	pointers->pool = pool_create();

	//Reading of constants.
	if (fh1->count_constant != 0)
	{
		string_buffer = (char*)malloc(fh1->size_of_constant);
		size = fread(string_buffer, fh1->size_of_constant, 1, program);
		if (1 != size) interpret_crash(wrng_file);
		substring = string_buffer;
		for (i = 1; i <= fh1->count_constant; i++)
		{			
			add_const(i, pointers->pool, substring); 
			substring += strlen(substring) + 1;
		}
		free(string_buffer);
	}

	//Reading of the second part of file-header.
	fh2 = (file_header2*)malloc(sizeof(file_header2));
	size = fread(fh2, sizeof(file_header2), 1, program);
	if (size != 1) interpret_crash(wrng_file);

	//Reading of functions.
	pointers->count_of_functions = fh2->count_function; //Is it an important knoledge?..
	pointers->table = (function_table*)malloc(sizeof(function_table) * fh2->count_function);
	mh1 = (function_header1*)malloc(sizeof(function_header1));
	mh2 = (function_header2*)malloc(sizeof(function_header2));
	for (i = 0; i < fh2->count_function; i++)
	{
		size = fread(mh1, sizeof(function_header1), 1, program);
		if (1 != size) interpret_crash(wrng_file);
		pointers->byte_code = (function)realloc(pointers->byte_code, current_offset + mh1->size_of_byte_code);
		size = fread((pointers->byte_code + current_offset), mh1->size_of_byte_code, 1, program);
		if (1 != size) interpret_crash(wrng_file);
		size = fread(mh2, sizeof(function_header2), 1, program);
		if (1 != size) interpret_crash(wrng_file);
		(pointers->table + i)->id = mh2->id;
		(pointers->table + i)->offset = pointers->byte_code + current_offset;
		if (mh2->id == fh2->entry_point_id) pointers->ip = pointers->byte_code + current_offset;
		current_offset += mh1->size_of_byte_code;
	}
	free(fh1);
	free(fh2);
	free(mh1);
	free(mh2);
	fclose(program);
	return *pointers;
}