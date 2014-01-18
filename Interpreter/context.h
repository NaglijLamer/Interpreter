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

//Context (like stack frame).
typedef struct{
	function return_address;
	stack_t* locals;
}context_t;

//Function (for "hash"-table where key is id).
typedef struct{
	unsigned short id;
	unsigned short locals;
	function offset;
	context_t* ctx;
	unsigned int ctx_count;
}function_table;







#endif