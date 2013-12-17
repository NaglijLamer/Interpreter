//File with switch(byte_code_command) and some functions for stack.

#include <stdio.h>
#include <stdlib.h>
#include "interpreter.h"
#include "for_byte-codes.h"

#define TRUE 1
#define ZERO_OFFSET -1
#define START_SIZE 100

//Increasing of stack size.
void static stack_realloc(pointers* stack)
{
	stack->size_of_stack <<= 1;
	stack->bottom = (stack_t*)realloc(stack->bottom, stack->size_of_stack);
	if (stack->bottom == NULL) interpret_crash(stck_overflow);
}

/*Instructions.*/

//Invalid instruction.
void static command_INVALID(pointers* stack)
{
	interpret_crash(inval_instr);
}

//Load double on TOS, inlined into insn stream.
void static command_DLOAD(pointers* stack)
{
	if (stack->offset + 1 >= stack->size_of_stack) stack_realloc(stack);
	stack->offset++;
	(stack->offset + stack->bottom)->dnumber = *((double*)(++stack->ip));
	stack->ip += 7;
}

//Load int on TOS, inlined into insn stream.
void static command_ILOAD(pointers* stack)
{
	if (stack->offset + 1 >= stack->size_of_stack) stack_realloc(stack);
	stack->offset++;
	(stack->offset + stack->bottom)->inumber = *((long long*)(++stack->ip));
	stack->ip += 7;
}

//Load string reference on TOS, next two bytes - constant id.
void static command_SLOAD(pointers* stack)
{
	if (stack->offset + 1 >= stack->size_of_stack) stack_realloc(stack);
	stack->offset++;
	(stack->offset + stack->bottom)->str = (++stack->ip);
}

//Load double 0 on TOS.
void static command_DLOAD0(pointers* stack)
{
	if (stack->offset + 1 >= stack->size_of_stack) stack_realloc(stack);
	stack->offset++;
	(stack->offset + stack->bottom)->dnumber = 0.0;
}

//Load int 0 on TOS.
void static command_ILOAD0(pointers* stack)
{
	if (stack->offset + 1 >= stack->size_of_stack) stack_realloc(stack);
	stack->offset++;
	(stack->offset + stack->bottom)->inumber = 0;
}

//Load empty string on TOS.
/* !!! Empty string?? !!! */
void static command_SLOAD0(pointers* stack)
{
	if (stack->offset + 1 >= stack->size_of_stack) stack_realloc(stack);
	stack->offset++;
	(stack->offset + stack->bottom)->str = NULL;
}

//Load double 1 on TOS.
void static command_DLOAD1(pointers* stack)
{
	if (stack->offset + 1 >= stack->size_of_stack) stack_realloc(stack);
	stack->offset++;
	(stack->offset + stack->bottom)->dnumber = 1.0;
}

//Load int 1 on TOS.
void static command_ILOAD1(pointers* stack)
{
	if (stack->offset + 1 >= stack->size_of_stack) stack_realloc(stack);
	stack->offset++;
	(stack->offset + stack->bottom)->inumber = 1;
}

//Load double -1 on TOS.
void static command_DLOADM1(pointers* stack)
{
	if (stack->offset + 1 >= stack->size_of_stack) stack_realloc(stack);
	stack->offset++;
	(stack->offset + stack->bottom)->dnumber = -1.0;
}

//Load int -1 on TOS.
void static command_ILOADM1(pointers* stack)
{
	if (stack->offset + 1 >= stack->size_of_stack) stack_realloc(stack);
	stack->offset++;
	(stack->offset + stack->bottom)->inumber = -1;
}

//Add 2 doubles on TOS, push value back.
void static command_DADD(pointers* stack)
{
	if (stack->offset - 2 < ZERO_OFFSET) interpret_crash(stck_empt);
	stack->offset--;
	(stack->bottom + stack->offset)->dnumber += (stack->bottom + stack->offset + 1)->dnumber;
}

//Add 2 ints on TOS, push value back.
void static command_IADD(pointers* stack)
{
	if (stack->offset - 2 < ZERO_OFFSET) interpret_crash(stck_empt);
	stack->offset--;
	(stack->bottom + stack->offset)->inumber += (stack->bottom + stack->offset + 1)->inumber;
}

//Subtract 2 doubles on TOS (lower from upper), push value back.
void static command_DSUB(pointers* stack)
{
	if (stack->offset - 2 < ZERO_OFFSET) interpret_crash(stck_empt);
	stack->offset--;
	(stack->bottom + stack->offset)->dnumber = (stack->bottom + stack->offset + 1)->dnumber - (stack->bottom + stack->offset)->dnumber;
}

//Subtract 2 ints on TOS (lower from upper), push value back.
void static command_ISUB(pointers* stack)
{
	if (stack->offset - 2 < ZERO_OFFSET) interpret_crash(stck_empt);
	stack->offset--;
	(stack->bottom + stack->offset)->inumber = (stack->bottom + stack->offset + 1)->inumber - (stack->bottom + stack->offset)->inumber;
}

//Multiply 2 doubles on TOS, push value back.
void static command_DMUL(pointers* stack)
{
	if (stack->offset - 2 < ZERO_OFFSET) interpret_crash(stck_empt);
	stack->offset--;
	(stack->bottom + stack->offset)->dnumber *= (stack->bottom + stack->offset + 1)->dnumber;
}

//Multiply 2 ints on TOS, push value back.
void static command_IMUL(pointers* stack)
{
	if (stack->offset - 2 < ZERO_OFFSET) interpret_crash(stck_empt);
	stack->offset--;
	(stack->bottom + stack->offset)->inumber *= (stack->bottom + stack->offset + 1)->inumber;
}

//Divide 2 doubles on TOS (upper to lower), push value back.
void static command_DDIV(pointers* stack)
{
	if (stack->offset - 2 < ZERO_OFFSET) interpret_crash(stck_empt);
	stack->offset--;
	(stack->bottom + stack->offset)->dnumber = (stack->bottom + stack->offset + 1)->dnumber / (stack->bottom + stack->offset)->dnumber;
}

//Divide 2 ints on TOS (upper to lower), push value back.
void static command_IDIV(pointers* stack)
{
	if (stack->offset - 2 < ZERO_OFFSET) interpret_crash(stck_empt);
	stack->offset--;
	(stack->bottom + stack->offset)->inumber = (stack->bottom + stack->offset + 1)->inumber / (stack->bottom + stack->offset)->inumber;
}

//Modulo operation on 2 ints on TOS (upper to lower), push value back.
void static command_IMOD(pointers* stack)
{
	if (stack->offset - 2 < ZERO_OFFSET) interpret_crash(stck_empt);
	stack->offset--;
	(stack->bottom + stack->offset)->inumber = (stack->bottom + stack->offset + 1)->inumber % (stack->bottom + stack->offset)->inumber;
}

//Negate double on TOS.
void static command_DNEG(pointers* stack)
{
	if (stack->offset - 1 < ZERO_OFFSET) interpret_crash(stck_empt);
	(stack->bottom + stack->offset)->dnumber = -((stack->bottom + stack->offset)->dnumber);
}

//Negate int on TOS.
void static command_INEG(pointers* stack)
{
	if (stack->offset - 1 < ZERO_OFFSET) interpret_crash(stck_empt);
	(stack->bottom + stack->offset)->inumber = -((stack->bottom + stack->offset)->inumber);
}

//Pop and print integer TOS.
void static command_IPRINT(pointers* stack)
{
	if (stack->offset - 1 < ZERO_OFFSET) interpret_crash(stck_empt);
	printf("%d\n", (stack->bottom + stack->offset)->inumber);
}

//Pop and print double TOS.
void static command_DPRINT(pointers* stack)
{
	if (stack->offset - 1 < ZERO_OFFSET) interpret_crash(stck_empt);
	printf("%f\n", (stack->bottom + stack->offset)->dnumber);
}

//Pop and print string TOS.
void static command_SPRINT(pointers* stack)
{
	if (stack->offset - 1 < ZERO_OFFSET) interpret_crash(stck_empt);
	printf("%s\n", *((stack->bottom + stack->offset)->str));
}

//Convert int on TOS to double.
void static command_I2D(pointers* stack)
{
	if (stack->offset - 1 < ZERO_OFFSET) interpret_crash(stck_empt);	
	(stack->bottom + stack->offset)->dnumber = (double)((stack->bottom + stack->offset)->inumber);
}

//Convert double on TOS to int.
void static command_D2I(pointers* stack)
{
	if (stack->offset - 1 < ZERO_OFFSET) interpret_crash(stck_empt);	
	(stack->bottom + stack->offset)->inumber = (int)((stack->bottom + stack->offset)->dnumber);
}

//Convert string on TOS to int.
void static command_S2I(pointers* stack)
{
	if (stack->offset - 1 < ZERO_OFFSET) interpret_crash(stck_empt);
	(stack->bottom + stack->offset)->inumber = atoi((stack->bottom + stack->offset)->str);
}

//Swap 2 topmost values.
void static command_SWAP(pointers* stack)
{
	stack_t top;
	if (stack->offset - 2 <= ZERO_OFFSET) interpret_crash(stck_empt);
	top = *(stack->bottom + stack->offset);
	*(stack->bottom + stack->offset) = *(stack->bottom + stack->offset - 1);
	*(stack->bottom + stack->offset - 1) = top;
}

//Remove topmost value.
void static command_POP(pointers* stack)
{
	if (stack->offset - 1 < ZERO_OFFSET) interpret_crash(stck_empt);
	stack->offset--;
}

//Load double from variable 0, push on TOS.
void static command_LOADDVAR0(pointers* stack)
{
}

//Load double from variable 1, push on TOS.
void static command_LOADDVAR1(pointers* stack)
{
}

//Load double from variable 2, push on TOS.
void static command_LOADDVAR2(pointers* stack)
{
}

//Load double from variable 3, push on TOS.
void static command_LOADDVAR3(pointers* stack)
{
}

//Load int from variable 0, push on TOS.
void static command_LOADIVAR0(pointers* stack)
{
}

//Load int from variable 1, push on TOS.
void static command_LOADIVAR1(pointers* stack)
{
}

//Load int from variable 2, push on TOS.
void static command_LOADIVAR2(pointers* stack)
{
}

//Load int from variable 3, push on TOS.
void static command_LOADIVAR3(pointers* stack)
{
}

//Load string from variable 0, push on TOS.
void static command_LOADSVAR0(pointers* stack)
{
}

//Load string from variable 1, push on TOS.
void static command_LOADSVAR1(pointers* stack)
{
}

//Load string from variable 2, push on TOS.
void static command_LOADSVAR2(pointers* stack)
{
}

//Load string from variable 3, push on TOS.
void static command_LOADSVAR3(pointers* stack)
{
}

//Pop TOS and store to double variable 0, push on TOS.
void static command_STOREDVAR0(pointers* stack)
{
}

//Pop TOS and store to double variable 1, push on TOS.
void static command_STOREDVAR1(pointers* stack)
{
}

//Pop TOS and store to double variable 2, push on TOS.
void static command_STOREDVAR2(pointers* stack)
{
}

//Pop TOS and store to double variable 3, push on TOS.
void static command_STOREDVAR3(pointers* stack)
{
}

//Pop TOS and store to int variable 0, push on TOS.
void static command_STOREIVAR0(pointers* stack)
{
}

//Pop TOS and store to int variable 1, push on TOS.
void static command_STOREIVAR1(pointers* stack)
{
}

//Pop TOS and store to int variable 2, push on TOS.
void static command_STOREIVAR2(pointers* stack)
{
}

//Pop TOS and store to int variable 3, push on TOS.
void static command_STOREIVAR3(pointers* stack)
{
}

//Pop TOS and store to string variable 0, push on TOS.
void static command_STORESVAR0(pointers* stack)
{
}

//Pop TOS and store to string variable 1, push on TOS.
void static command_STORESVAR1(pointers* stack)
{
}

//Pop TOS and store to string variable 2, push on TOS.
void static command_STORESVAR2(pointers* stack)
{
}

//Pop TOS and store to string variable 3, push on TOS.
void static command_STORESVAR3(pointers* stack)
{
}

//Load double from variable, whose 2-byte id is inlined to insn stream, push on TOS.
void static command_LOADDVAR(pointers* stack)
{
}

//Load int from variable, whose 2-byte id is inlined to insn stream, push on TOS.
void static command_LOADIVAR(pointers* stack)
{
}

//Load string from variable, whose 2-byte id is inlined to insn stream, push on TOS.
void static command_LOADSVAR(pointers* stack)
{
}

//Pop TOS and store to double variable, whose 2-byte id is inlined to insn stream.
void static command_STOREDVAR(pointers* stack)
{
}

//Pop TOS and store to int variable, whose 2-byte id is inlined to insn stream.
void static command_STOREIVAR(pointers* stack)
{
}

//Pop TOS and store to string variable, whose 2-byte id is inlined to insn stream.
void static command_STORESVAR(pointers* stack)
{
}

//Load double from variable, whose 2-byte context and 2-byte id inlined to insn stream, push on TOS.
void static command_LOADCTXDVAR(pointers* stack)
{
}

//Load int from variable, whose 2-byte context and 2-byte id inlined to insn stream, push on TOS.
void static command_LOADCTXIVAR(pointers* stack)
{
}

//Load string from variable, whose 2-byte context and 2-byte id inlined to insn stream, push on TOS.
void static command_LOADCTXSVAR(pointers* stack)
{
}

//Pop TOS and store to double variable, whose 2-byte context and 2-byte id is inlined to insn stream.
void static command_STORECTXDVAR(pointers* stack)
{
}

//Pop TOS and store to int variable, whose 2-byte context and 2-byte id is inlined to insn stream.
void static command_STORECTXIVAR(pointers* stack)
{
}

//Pop TOS and store to string variable, whose 2-byte context and 2-byte id is inlined to insn stream.
void static command_STORECTXSVAR(pointers* stack)
{
}

//Compare 2 topmost doubles, pushing libc-stryle comparator value cmp(upper, lower) as integer.
void static command_DCMP(pointers* stack)
{
	if (stack->offset - 2 <= ZERO_OFFSET) interpret_crash(stck_empt);
	if ((stack->bottom + stack->offset - 1)->dnumber > (stack->bottom + stack->offset - 2)->dnumber) command_DLOAD1(stack);
	else if ((stack->bottom + stack->offset - 1)->dnumber < (stack->bottom + stack->offset - 2)->dnumber) command_DLOADM1(stack);
	else command_DLOAD0(stack);
}

//Compare 2 topmost ints, pushing libc-style comparator value cmp(upper, lower) as integer.
void static command_ICMP(pointers* stack)
{
	if (stack->offset - 2 <= ZERO_OFFSET) interpret_crash(stck_empt);
	if ((stack->bottom + stack->offset - 1)->inumber > (stack->bottom + stack->offset - 2)->inumber) command_ILOAD1(stack);
	else if ((stack->bottom + stack->offset - 1)->inumber < (stack->bottom + stack->offset - 2)->inumber) command_ILOADM1(stack);
	else command_ILOAD0(stack);
}

//Jump always, next two bytes - signed offset of jump destination.
void static command_JA(pointers* stack)
{
}

//Compare two topmost integers and jump if upper != lower, next two bytes - signed offset of jump destination.
void static command_IFICMPNE(pointers* stack)
{
}

//Compare two topmost integers and jump if upper == lower, next two bytes - signed offset of jump destination.
void static command_IFICMPE(pointers* stack)
{
}

//Compare two topmost integers and jump if upper > lower, next two bytes - signed offset of jump destination.
void static command_IFICMPG(pointers* stack)
{
}

//Compare two topmost integers and jump if upper >= lower, next two bytes - signed offset of jump destination.
void static command_IFICMPGE(pointers* stack)
{
}

//Compare two topmost integers and jump if upper < lower, next two bytes - signed offset of jump destination.
void static command_IFICMPL(pointers* stack)
{
}

//Compare two topmost integers and jump if upper <= lower, next two bytes - signed offset of jump destination.
void static command_IFICMPLE(pointers* stack)
{
}

//Dump value on TOS, without removing it.
void static command_DUMP(pointers* stack)
{
	if (!(stack->offset - 1 < ZERO_OFFSET)) 
		printf("Int %d\nDouble %f\nString %s\n", (stack->bottom + stack->offset)->inumber, 
		(stack->bottom + stack->offset)->dnumber, *((stack->bottom + stack->offset)->str));
}

//Stop execution.
void static command_STOP(pointers* stack)
{
	interpret_crash(stp_commnd);
}

//Call function, next two bytes - unsigned function id.
void static command_CALL(pointers* stack)
{
}

//Call native function, next two bytes - id of the native function.
void static command_CALLNATIVE(pointers* stack)
{
}

//Return to call location.
void static command_RETURN(pointers* stack)
{
}

//Breakpoint for the debugger.
void static command_BREAK(pointers* stack)
{
}

/*End of Instructions*/

//Interpeter body. Really.
int interpreter(functions byte_code, uint entry_point_id, uint size_of_byte_code)
{
	//Instruction pointer
	uint current_id = entry_point_id;
	//Initialization of stack size.
	pointers stack;
	stack.offset = ZERO_OFFSET;
	stack.size_of_stack = START_SIZE;
	stack.bottom = (stack_t*)malloc(sizeof(stack_t) * stack.size_of_stack);

	stack.ip = (function)(byte_code + current_id);
	//Here we must create constant pull - an array with constants, where number of element is a constant id.
	//VERY BIG SWITCH! VERY. BIG.
	while (TRUE)
	{
		switch(*stack.ip)
		{
			#define CASE(code, l) case code : command_##code (&stack); break;
				FOR_BYTECODES( CASE )
			/*case INVALID: command_INVALID(); break;
			case ILOAD: 
				{
					command_ILOAD(&stack, *((long long*)(current_function + (++ip)))); 
					ip += 7;
					nextbyte = *(current_function + ip); 
					break;
				}
			case IADD: command_IADD(&stack); break;
			case IPRINT: command_IPRINT(&stack); break;
			case STOP: return stp_commnd;*/
		}
		stack.ip++;
	}
}