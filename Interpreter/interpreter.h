#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "instant_exit.h"
#include "context.h"

//typedef char* function;
//typedef function* functions;
typedef unsigned int uint;
typedef unsigned short ushort;

//Stack of calculations, pointer to the pool of constant, instruction pointer.
typedef struct
{
	stack_t* bottom;		//Bottom of stack,
	stack_t* sp;			//Stack Pointer.
	stack_t* head;			//= bottom + head = maxSP.
	function ip;			//Instruction Pointer.
	function byte_code;		//Pointer to the byte_code.
	char** pool;			//Pointer for a constant pool.
	function_table* table;	//Comparison of function ids and offsets.
	function_table* current_function; //Current function for using locals.
	uint count_functions;	//Count of functions.
}registers;

int interpreter(registers* pointers);
void static stack_realloc(registers* pointers);
void registers_destruction(registers* pointers);

#endif