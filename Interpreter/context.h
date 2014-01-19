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
//Context (like stack frame).
typedef struct{
	function return_address;
	function_table* previous_function;
	stack_t* locals;
}context_t;

//Function (for "hash"-table where key is id).
struct function_table{
	unsigned short id;
	unsigned short locals;
	unsigned int offset;
	context_t* ctx;
	unsigned int ctx_count;
};

function_table* get_function(function_table* table, unsigned short id, int function_count);


#endif