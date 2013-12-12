#include <stdio.h>
#include <stdlib.h>
#include "interpreter.h"

//File with switch(byte_code_command) and some functions for stack.

//Push element on TOS.
void push(stack_t** stackp, string_t* value)
{
	stack_t* elem = (stack_t*)malloc(sizeof(stack_t));
	if (elem == NULL)
	{
		fputs("Error! Stack overflow", stderr);
		exit(2); 
	}
	elem->value = value;
	if (stackp != NULL) elem->next = *stackp;
	else elem->next = NULL;
	*stackp = elem;
}

//Pop element from TOS.
string_t* pop(stack_t** stackp)
{
	stack_t* TOS;
	string_t* TOS_value;
	if (*stackp == NULL)
	{
		fputs("Error! Stack is empty!", stderr);
		exit(2);
	}
	TOS = *stackp;
	TOS_value = TOS->value;
	*stackp = (*stackp)->next;
	free(TOS);
	return TOS_value;
}