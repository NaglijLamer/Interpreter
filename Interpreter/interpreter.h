#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "instant_exit.h"
#include "parser.h"

//Element in stack.
typedef union 
{
	long long inumber;
	double dnumber;
	long long str_id;
}stack_t;

//Stack.
typedef struct
{
	stack_t* bottom;	//Bottom of stack,
	stack_t* sp;		//Stack Pointer.
	stack_t* head;		//= bottom + head = maxSP.
	function ip;		//Instruction Pointer.
	char** pool;		//May be a pointer for a constant pool.
}registers;

int interpreter(functions byte_code, uint entry_point_id, uint size_of_byte_code, char** pool);
void static stack_realloc(registers* pointers);
void stack_destruction(registers* pointers);

#endif