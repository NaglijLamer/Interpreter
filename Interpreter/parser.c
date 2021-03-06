//File with functions that can read file with byte-code. And create an array from byte-code functions.

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#define SUCCESS 1
#define SIGNATURE 0xBABA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"
#include "parser.h"
#include "instant_exit.h"
#include "constant_pool.h"

//Parser of file.
registers* parser_file(FILE* program)
{
	registers* pointers;
	file_header1* fh1;
	file_header2* fh2;
	function_header1* mh1;
	function_header2* mh2;
	char *string_buffer, *substring;
	size_t size;
	int current_offset = 0;
	int entry_offset = 0;
	char load_entry = 0;
	uint i;

	//Reading of the first part of file-header.
	fh1 = (file_header1*)malloc(sizeof(file_header1));
	size = fread(fh1, sizeof(file_header1), 1, program);
	if (SUCCESS != size || fh1->signature != SIGNATURE) program_crash(wrng_file);

	//Creation of the constant pool.
	pointers = (registers*)malloc(sizeof(registers));
	pointers->pool = pool_create();

	//Reading of constants.
	if (fh1->count_constant != 0)
	{
		string_buffer = (char*)malloc(fh1->size_of_constant);
		size = fread(string_buffer, fh1->size_of_constant, 1, program);
		if (SUCCESS != size) program_crash(wrng_file);
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
	if (size != SUCCESS) program_crash(wrng_file);
	pointers->count_functions = fh2->count_function;

	//Initialization of some registers.
	pointers->table = (function_table*)malloc(sizeof(function_table) * fh2->count_function);
	pointers->ctxsp = pointers->ctx_bottom = (context_t*)malloc(sizeof(context_t) * FRAMES);
	pointers->byte_code = NULL;

	//Reading of functions.
	mh1 = (function_header1*)malloc(sizeof(function_header1));
	mh2 = (function_header2*)malloc(sizeof(function_header2));
	for (i = 0; i < fh2->count_function; i++)
	{
		size = fread(mh1, sizeof(function_header1), 1, program);
		if ((SUCCESS != size) & fseek(program, mh1->size_of_sign, SEEK_CUR)) program_crash(wrng_file);
		size = fread(mh2, sizeof(function_header2), 1, program);
		if (SUCCESS != size) program_crash(wrng_file);
		pointers->byte_code = (function)realloc(pointers->byte_code, current_offset + mh1->size_of_byte_code);
		size = fread((pointers->byte_code + current_offset), mh1->size_of_byte_code, 1, program);
		if (SUCCESS != size) program_crash(wrng_file);
		//Initialization of function metadata.
		(pointers->table + i)->id = mh2->id;
		(pointers->table + i)->offset = current_offset;
		(pointers->table + i)->locals = mh2->count_of_locals;
		(pointers->table + i)->args = mh2->count_of_arguments;
		(pointers->table + i)->ctx = NULL;
		//If this function is an entry point to program...
		if (mh2->id == fh2->entry_point_id) 
			{
				load_entry = SUCCESS;
				entry_offset = current_offset;
				pointers->current_function = (pointers->table + i);
				pointers->ctxsp->locals = (stack_t*)malloc(sizeof(stack_t) * mh2->count_of_locals);
				pointers->ctxsp->previous_ctx = NULL;
				pointers->ctxsp->previous_function = NULL;
				pointers->ctxsp->return_address = NULL;
				pointers->current_function->ctx = pointers->ctxsp;
				//Now this function ready for execution.
			}
		current_offset += mh1->size_of_byte_code;
	}
	if (load_entry != SUCCESS) program_crash(no_entr_funct);
	pointers->ip = pointers->byte_code + entry_offset;
	free(fh1);
	free(fh2);
	free(mh1);
	free(mh2);
	fclose(program);
	return pointers;
}