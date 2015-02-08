#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "instant_exit.h"
#include "context.h"

//Nice names of types.
typedef unsigned int uint;
typedef unsigned short ushort;

//Stack of calculations, pointer to the pool of constant, instruction pointer.
typedef struct
{
	stack_t* bottom;					//Bottom of stack,
	stack_t* sp;						//Stack Pointer of calculational stack.
	stack_t* head;						//= bottom + head = maxSP.
	function ip;						//Instruction Pointer.
	function byte_code;					//Pointer to the byte_code.
	char** pool;						//Pointer for a constant pool.
	function_table* table;				//Comparison of function ids and offsets.
	function_table* current_function;	//Current function for using locals.
	uint count_functions;				//Count of functions.
	context_t *ctx_bottom;				//Bottom of context stack.
	context_t *ctxsp;					//Stack Pointer of context stack.
}registers;

//Main function of interpreter.
int interpreter(registers* pointers);
//Function to reallocate calculation stack. Maybe - unusable in future.
void static stack_realloc(registers* pointers);
//Handler of critical runtime errors in interpreter.
void interpret_crash(int err_code, registers* pointers);
//Free all registers.
void registers_destruction(registers* pointers);

#endif