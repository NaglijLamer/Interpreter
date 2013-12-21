#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "instant_exit.h"

//Element in stack.
typedef union 
{
	long long inumber;
	double dnumber;
	long long str_id;
}stack_t;

typedef char* function;
//typedef function* functions;
typedef unsigned int uint;
typedef unsigned short ushort;

typedef struct{
	short id;
	function offset;
}function_table;

//Stack of calculations, pointer to the pool of constant, instruction pointer.
typedef struct
{
	stack_t* bottom;		//Bottom of stack,
	stack_t* sp;			//Stack Pointer.
	stack_t* head;			//= bottom + head = maxSP.
	function ip;			//Instruction Pointer.
	function byte_code;		//Pointer to the byte_code.
	char** pool;			//May be a pointer for a constant pool.
	function_table* table;	//Comparison of function ids and offsets.
	uint count_of_functions;
}registers;

int interpreter(registers pointers);
void static stack_realloc(registers* pointers);
void registers_destruction(registers* pointers);

#endif