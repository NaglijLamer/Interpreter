//File with switch(byte_code_command) and some functions for stack.

#include <stdio.h>
#include <stdlib.h>
#include "interpreter.h"

#define true 1
#define zero_offset -1
#define start_size 100

//Increasing of stack size.
void static stack_realloc(current_stack_t* stack)
{
	stack->size_of_stack <<= 1;
	stack->bottom = (stack_t*)realloc(stack->bottom, stack->size_of_stack);
	if (stack->bottom == NULL) interpret_crash(stck_overflow);
}

/*Instructions.*/

//Invalid instruction.
void static command_INVALID()
{
	interpret_crash(inval_instr);
}

//Load double on TOS, inlined into insn stream.
void static command_DLOAD(current_stack_t* stack, double d)
{
	if (stack->offset + 1 >= stack->size_of_stack) stack_realloc(stack);
	stack->offset++;
	(stack->offset + stack->bottom)->dnumber = d;
}

//Load int on TOS, inlined into insn stream.
void static command_ILOAD(current_stack_t* stack, int i)
{
	if (stack->offset + 1 >= stack->size_of_stack) stack_realloc(stack);
	stack->offset++;
	(stack->offset + stack->bottom)->inumber = i;
}

//Load string reference on TOS, next two bytes - constant id.
void static command_SLOAD(current_stack_t* stack, char* s)
{
	if (stack->offset + 1 >= stack->size_of_stack) stack_realloc(stack);
	stack->offset++;
	(stack->offset + stack->bottom)->str = s;
}

//Load double 0 on TOS.
void static command_DLOAD0(current_stack_t* stack)
{
	command_DLOAD(stack, 0.0);
}

//Load int 0 on TOS.
void static command_ILOAD0(current_stack_t* stack)
{
	command_ILOAD(stack, 0);
}

//Load empty string on TOS.
/* !!! Empty string?? !!! */
void static command_SLOAD0(current_stack_t* stack)
{
	command_SLOAD(stack, NULL);
}

//Load double 1 on TOS.
void static command_DLOAD1(current_stack_t* stack)
{
	command_DLOAD(stack, 1.0);
}

//Load int 1 on TOS.
void static command_ILOAD1(current_stack_t* stack)
{
	command_ILOAD(stack, 1);
}

//Load double -1 on TOS.
void static command_DLOADM1(current_stack_t* stack)
{
	command_DLOAD(stack, -1.0);
}

//Load int -1 on TOS.
void static command_ILOADM1(current_stack_t* stack)
{
	command_ILOAD(stack, -1);
}

//Add 2 doubles on TOS, push value back.
void static command_DADD(current_stack_t* stack)
{
	if (stack->offset - 2 < zero_offset) interpret_crash(stck_empt);
	stack->offset--;
	(stack->bottom + stack->offset)->dnumber += (stack->bottom + stack->offset + 1)->dnumber;
}

//Add 2 ints on TOS, push value back.
void static command_IADD(current_stack_t* stack)
{
	if (stack->offset - 2 < zero_offset) interpret_crash(stck_empt);
	stack->offset--;
	(stack->bottom + stack->offset)->inumber += (stack->bottom + stack->offset + 1)->inumber;
}

//Subtract 2 doubles on TOS (lower from upper), push value back.
void static command_DSUB(current_stack_t* stack)
{
	if (stack->offset - 2 < zero_offset) interpret_crash(stck_empt);
	stack->offset--;
	(stack->bottom + stack->offset)->dnumber = (stack->bottom + stack->offset + 1)->dnumber - (stack->bottom + stack->offset)->dnumber;
}

//Subtract 2 ints on TOS (lower from upper), push value back.
void static command_ISUB(current_stack_t* stack)
{
	if (stack->offset - 2 < zero_offset) interpret_crash(stck_empt);
	stack->offset--;
	(stack->bottom + stack->offset)->inumber = (stack->bottom + stack->offset + 1)->inumber - (stack->bottom + stack->offset)->inumber;
}

//Multiply 2 doubles on TOS, push value back.
void static command_DMUL(current_stack_t* stack)
{
	if (stack->offset - 2 < zero_offset) interpret_crash(stck_empt);
	stack->offset--;
	(stack->bottom + stack->offset)->dnumber *= (stack->bottom + stack->offset + 1)->dnumber;
}

//Multiply 2 ints on TOS, push value back.
void static command_IMUL(current_stack_t* stack)
{
	if (stack->offset - 2 < zero_offset) interpret_crash(stck_empt);
	stack->offset--;
	(stack->bottom + stack->offset)->inumber *= (stack->bottom + stack->offset + 1)->inumber;
}

//Divide 2 doubles on TOS (upper to lower), push value back.
void static command_DDIV(current_stack_t* stack)
{
	if (stack->offset - 2 < zero_offset) interpret_crash(stck_empt);
	stack->offset--;
	(stack->bottom + stack->offset)->dnumber = (stack->bottom + stack->offset + 1)->dnumber / (stack->bottom + stack->offset)->dnumber;
}

//Divide 2 ints on TOS (upper to lower), push value back.
void static command_IDIV(current_stack_t* stack)
{
	if (stack->offset - 2 < zero_offset) interpret_crash(stck_empt);
	stack->offset--;
	(stack->bottom + stack->offset)->inumber = (stack->bottom + stack->offset + 1)->inumber / (stack->bottom + stack->offset)->inumber;
}

//Modulo operation on 2 ints on TOS (upper to lower), push value back.
void static command_IMOD(current_stack_t* stack)
{
	if (stack->offset - 2 < zero_offset) interpret_crash(stck_empt);
	stack->offset--;
	(stack->bottom + stack->offset)->inumber = (stack->bottom + stack->offset + 1)->inumber % (stack->bottom + stack->offset)->inumber;
}

//Negate double on TOS.
void static command_DNEG(current_stack_t* stack)
{
	if (stack->offset - 1 < zero_offset) interpret_crash(stck_empt);
	(stack->bottom + stack->offset)->dnumber = -((stack->bottom + stack->offset)->dnumber);
}

//Negate int on TOS.
void static command_INEG(current_stack_t* stack)
{
	if (stack->offset - 1 < zero_offset) interpret_crash(stck_empt);
	(stack->bottom + stack->offset)->inumber = -((stack->bottom + stack->offset)->inumber);
}

//Pop and print integer TOS.
void static command_IPRINT(current_stack_t* stack)
{
	if (stack->offset - 1 < zero_offset) interpret_crash(stck_empt);
	printf("%d\n", (stack->bottom + stack->offset)->inumber);
}

//Pop and print double TOS.
void static command_DPRINT(current_stack_t* stack)
{
	if (stack->offset - 1 < zero_offset) interpret_crash(stck_empt);
	printf("%f\n", (stack->bottom + stack->offset)->dnumber);
}

//Pop and print string TOS.
void static command_SPRINT(current_stack_t* stack)
{
	if (stack->offset - 1 < zero_offset) interpret_crash(stck_empt);
	printf("%s\n", *((stack->bottom + stack->offset)->str));
}

//Convert int on TOS to double.
void static command_I2D(current_stack_t* stack)
{
	if (stack->offset - 1 < zero_offset) interpret_crash(stck_empt);	
	(stack->bottom + stack->offset)->dnumber = (double)((stack->bottom + stack->offset)->inumber);
}

//Convert double on TOS to int.
void static command_D2I(current_stack_t* stack)
{
	if (stack->offset - 1 < zero_offset) interpret_crash(stck_empt);	
	(stack->bottom + stack->offset)->inumber = (int)((stack->bottom + stack->offset)->dnumber);
}

//Convert string on TOS to int.
void static command_S2I(current_stack_t* stack)
{
	if (stack->offset - 1 < zero_offset) interpret_crash(stck_empt);
	(stack->bottom + stack->offset)->inumber = atoi((stack->bottom + stack->offset)->str);
}

//Swap 2 topmost values.
void static command_SWAP(current_stack_t* stack)
{
	stack_t top;
	if (stack->offset - 2 <= zero_offset) interpret_crash(stck_empt);
	top = *(stack->bottom + stack->offset);
	*(stack->bottom + stack->offset) = *(stack->bottom + stack->offset - 1);
	*(stack->bottom + stack->offset - 1) = top;
}

//Remove topmost value.
void static command_POP(current_stack_t* stack)
{
	if (stack->offset - 1 < zero_offset) interpret_crash(stck_empt);
	stack->offset--;
}

/*	Commands, that can works woth variables.	*/

//Compare 2 topmost doubles, pushing libc-stryle comparator value cmp(upper, lower) as integer.
void static command_DCMP(current_stack_t* stack)
{
	if (stack->offset - 2 <= zero_offset) interpret_crash(stck_empt);
	if ((stack->bottom + stack->offset - 1)->dnumber > (stack->bottom + stack->offset - 2)->dnumber) command_DLOAD1(stack);
	else if ((stack->bottom + stack->offset - 1)->dnumber < (stack->bottom + stack->offset - 2)->dnumber) command_DLOADM1(stack);
	else command_DLOAD0(stack);
}

//Compare 2 topmost ints, pushing libc-style comparator value cmp(upper, lower) as integer.
void static command_ICMP(current_stack_t* stack)
{
	if (stack->offset - 2 <= zero_offset) interpret_crash(stck_empt);
	if ((stack->bottom + stack->offset - 1)->inumber > (stack->bottom + stack->offset - 2)->inumber) command_ILOAD1(stack);
	else if ((stack->bottom + stack->offset - 1)->inumber < (stack->bottom + stack->offset - 2)->inumber) command_ILOADM1(stack);
	else command_ILOAD0(stack);
}

/*	Commands, that can compare and jump.	*/

//Dump value on TOS, without removing it.
void static command_DUMP(current_stack_t* stack)
{
	if (!(stack->offset - 1 < zero_offset)) 
		printf("Int %d\nDouble %f\nString %s\n", (stack->bottom + stack->offset)->inumber, 
		(stack->bottom + stack->offset)->dnumber, *((stack->bottom + stack->offset)->str));
}

//Stop execution.
void static command_STOP()
{
	interpret_crash(stp_commnd);
}

/*	Commands, that can call functions and return from them.	*/
/*	Command, that can debug it.	*/

//Interpeter body. Really.
int interpreter(functions byte_code, uint entry_point_id, uint size_of_byte_code)
{
	char nextbyte;
	//Instruction pointer
	uint ip = 0;
	uint current_id = entry_point_id;
	function current_function;
	//Initialization of stack size.
	current_stack_t stack;
	stack.offset = zero_offset;
	stack.size_of_stack = start_size;
	stack.bottom = (stack_t*)malloc(sizeof(stack_t) * stack.size_of_stack);

	current_function = (function)(byte_code + current_id);
	//Here we must create constant pull - an array with constants, where number of element is a constant id.

	nextbyte = *(current_function + ip);
	//VERY BIG SWITCH! VERY. BIG.
	while (true)
	{
		switch(nextbyte)
		{
			case INVALID: command_INVALID(); break;
				//Fix it as 8-bytes integer. Not 1-byte char.
			case ILOAD: nextbyte = *(current_function + (++ip)); command_ILOAD(&stack, nextbyte); break;
			case IADD: command_IADD(&stack); break;
			case IPRINT: command_IPRINT(&stack); break;
			case STOP: return stp_commnd;
		}
		nextbyte = *(current_function + (++ip));
	}
}