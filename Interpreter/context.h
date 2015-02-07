#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <stdlib.h>
#define FRAMES 2048

typedef char* function;

//Element in stack.
typedef union 
{
	long long inumber;
	double dnumber;
	long long str_id;
}stack_t;

typedef struct function_table function_table;
typedef struct context_t context_t;

//Context (like stack frame).
struct context_t{
	function return_address;			//Return address to the previous function.
	function_table* previous_function;	//Pointer to the callee function.
	stack_t* locals;					//Array of local variables.
	context_t *previous_ctx;			//Pointer to the previous context of this function.
};

//Function.
struct function_table{
	unsigned short id;		//Function unique id.
	unsigned int locals;	//Count of function locals.
	unsigned int args;		//Count of function args.
	unsigned int offset;	//Start position of function in byte_code.
	context_t* ctx;			//Pointer to the last context of this function.
};

//Search function in table of functions by its id. Not nice.
function_table* get_function(function_table* table, unsigned short id, int function_count);


#endif