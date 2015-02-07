//File with switch(byte_code_command) and some functions for pointers.

#include <stdio.h>
#include "interpreter.h"
#include "commands.h"
#include "constant_pool.h"

#ifdef _MSC_VER
#define INLINE __forceinline
#else 
#define INLINE __attribute__((always_inline))
#endif

#define TRUE 1
#define ZERO_OFFSET -1
#define START_SIZE 100

//Increasing of pointers size.
void static stack_realloc(registers* pointers)
{
	size_t size, offset;
	size = (pointers->head - pointers->bottom) << 1;
	offset = pointers->sp - pointers->bottom;
	pointers->bottom = (stack_t*)realloc(pointers->bottom, size);
	if (pointers->bottom == NULL) interpret_crash(stck_overflow, pointers);
	pointers->head = pointers->bottom + size;
	pointers->sp = pointers->bottom + offset;
}

/*Instructions.*/

//Invalid instruction.
void static INLINE command_INVALID(registers* pointers)
{
	interpret_crash(inval_instr, pointers);
}

//Load double on TOS, inlined into insn stream.
void static INLINE command_DLOAD(registers* pointers)
{
	if (pointers->sp  >= pointers->head) stack_realloc(pointers);
	pointers->sp++;
	(pointers->sp)->dnumber = *((double*)(++pointers->ip));
	pointers->ip += 7;
}

//Load int on TOS, inlined into insn stream.
void static INLINE command_ILOAD(registers* pointers)
{
	if (pointers->sp >= pointers->head) stack_realloc(pointers);
	pointers->sp++;
	(pointers->sp)->inumber = *((long long*)(++pointers->ip));
	pointers->ip += 7;
}

//Load string reference on TOS, next two bytes - constant id.
void static INLINE command_SLOAD(registers* pointers)
{
	if (pointers->sp >= pointers->head) stack_realloc(pointers);
	pointers->sp++;
	(pointers->sp)->str_id = *((short*)(++pointers->ip));
	pointers->ip++;
}

//Load double 0 on TOS.
void static INLINE command_DLOAD0(registers* pointers)
{
	if (pointers->sp >= pointers->head) stack_realloc(pointers);
	pointers->sp++;
	(pointers->sp)->dnumber = 0.0;
}

//Load int 0 on TOS.
void static INLINE command_ILOAD0(registers* pointers)
{
	if (pointers->sp >= pointers->head) stack_realloc(pointers);
	pointers->sp++;
	(pointers->sp)->inumber = 0;
}

//Load empty string on TOS.
void static INLINE command_SLOAD0(registers* pointers)
{
	if (pointers->sp >= pointers->head) stack_realloc(pointers);
	pointers->sp++;
	(pointers->sp)->str_id = 0;
}

//Load double 1 on TOS.
void static INLINE command_DLOAD1(registers* pointers)
{
	if (pointers->sp >= pointers->head) stack_realloc(pointers);
	pointers->sp++;
	(pointers->sp)->dnumber = 1.0;
}

//Load int 1 on TOS.
void static INLINE command_ILOAD1(registers* pointers)
{
	if (pointers->sp >= pointers->head) stack_realloc(pointers);
	pointers->sp++;
	(pointers->sp)->inumber = 1;
}

//Load double -1 on TOS.
void static INLINE command_DLOADM1(registers* pointers)
{
	if (pointers->sp >= pointers->head) stack_realloc(pointers);
	pointers->sp++;
	(pointers->sp)->dnumber = -1.0;
}

//Load int -1 on TOS.
void static INLINE command_ILOADM1(registers* pointers)
{
	if (pointers->sp >= pointers->head) stack_realloc(pointers);
	pointers->sp++;
	(pointers->sp)->inumber = -1;
}

//Add 2 doubles on TOS, push value back.
void static INLINE command_DADD(registers* pointers)
{
	if ((pointers->sp - 1) < pointers->bottom) interpret_crash(stck_empt, pointers);
	pointers->sp--;
	(pointers->sp)->dnumber += (pointers->sp + 1)->dnumber;
}

//Add 2 ints on TOS, push value back.
void static INLINE command_IADD(registers* pointers)
{
	if ((pointers->sp - 1) < pointers->bottom) interpret_crash(stck_empt, pointers);
	pointers->sp--;
	(pointers->sp)->inumber += (pointers->sp + 1)->inumber;
}

//Subtract 2 doubles on TOS (lower from upper), push value back.
void static INLINE command_DSUB(registers* pointers)
{
	if ((pointers->sp - 1) < pointers->bottom) interpret_crash(stck_empt, pointers);
	pointers->sp--;
	(pointers->sp)->dnumber = (pointers->sp + 1)->dnumber - (pointers->sp)->dnumber;
}

//Subtract 2 ints on TOS (lower from upper), push value back.
void static INLINE command_ISUB(registers* pointers)
{
	if ((pointers->sp - 1) < pointers->bottom) interpret_crash(stck_empt, pointers);
	pointers->sp--;
	(pointers->sp)->inumber = (pointers->sp + 1)->inumber - (pointers->sp)->inumber;
}

//Multiply 2 doubles on TOS, push value back.
void static INLINE command_DMUL(registers* pointers)
{
	if ((pointers->sp - 1) < pointers->bottom) interpret_crash(stck_empt, pointers);
	pointers->sp--;
	(pointers->sp)->dnumber *= (pointers->sp + 1)->dnumber;
}

//Multiply 2 ints on TOS, push value back.
void static INLINE command_IMUL(registers* pointers)
{
	if ((pointers->sp - 1) < pointers->bottom) interpret_crash(stck_empt, pointers);
	pointers->sp--;
	(pointers->sp)->inumber *= (pointers->sp + 1)->inumber;
}

//Divide 2 doubles on TOS (upper to lower), push value back.
void static INLINE command_DDIV(registers* pointers)
{
	if ((pointers->sp - 1) < pointers->bottom) interpret_crash(stck_empt, pointers);
	pointers->sp--;
	(pointers->sp)->dnumber = (pointers->sp + 1)->dnumber / (pointers->sp)->dnumber;
}

//Divide 2 ints on TOS (upper to lower), push value back.
void static INLINE command_IDIV(registers* pointers)
{
	if ((pointers->sp - 1) < pointers->bottom) interpret_crash(stck_empt, pointers);
	pointers->sp--;
	(pointers->sp)->inumber = (pointers->sp + 1)->inumber / (pointers->sp)->inumber;
}

//Modulo operation on 2 ints on TOS (upper to lower), push value back.
void static INLINE command_IMOD(registers* pointers)
{
	if ((pointers->sp - 1) < pointers->bottom) interpret_crash(stck_empt, pointers);
	pointers->sp--;
	(pointers->sp)->inumber = (pointers->sp + 1)->inumber % (pointers->sp)->inumber;
}

//Negate double on TOS.
void static INLINE command_DNEG(registers* pointers)
{
	if (pointers->sp < pointers->bottom) interpret_crash(stck_empt, pointers);
	(pointers->sp)->dnumber = -((pointers->sp)->dnumber);
}

//Negate int on TOS.
void static INLINE command_INEG(registers* pointers)
{
	if (pointers->sp < pointers->bottom) interpret_crash(stck_empt, pointers);
	(pointers->sp)->inumber = -((pointers->sp)->inumber);
}

//Arithmetic OR of 2 ints on TOS, push value back.
void static INLINE command_IAOR(registers* pointers)
{
	if ((pointers->sp - 1) < pointers->bottom) interpret_crash(stck_empt, pointers);
	pointers->sp--;
	(pointers->sp)->inumber = (pointers->sp + 1)->inumber | (pointers->sp)->inumber;
}

//Arithmetic AND of 2 ints on TOS, push value back.
void static INLINE command_IAAND(registers* pointers)
{
	if ((pointers->sp - 1) < pointers->bottom) interpret_crash(stck_empt, pointers);
	pointers->sp--;
	(pointers->sp)->inumber = (pointers->sp + 1)->inumber & (pointers->sp)->inumber;
}

//Arithmetic XOR of 2 ints on TOS, push value back.
void static INLINE command_IAXOR(registers* pointers)
{
	if ((pointers->sp - 1) < pointers->bottom) interpret_crash(stck_empt, pointers);
	pointers->sp--;
	(pointers->sp)->inumber = (pointers->sp + 1)->inumber ^ (pointers->sp)->inumber;
}

//Pop and print integer TOS.
void static INLINE command_IPRINT(registers* pointers)
{
	if (pointers->sp < pointers->bottom) interpret_crash(stck_empt, pointers);
	printf("%lld\n", (pointers->sp)->inumber);
}

//Pop and print double TOS.
void static INLINE command_DPRINT(registers* pointers)
{
	if (pointers->sp < pointers->bottom) interpret_crash(stck_empt, pointers);
	printf("%f\n", (pointers->sp)->dnumber);
}

//Pop and print string TOS.
void static INLINE command_SPRINT(registers* pointers)
{
	if (pointers->sp < pointers->bottom) interpret_crash(stck_empt, pointers);
	printf("%s\n",  get_const((short)((pointers->sp)->str_id), pointers->pool));
}

//Convert int on TOS to double.
void static INLINE command_I2D(registers* pointers)
{
	if (pointers->sp < pointers->bottom) interpret_crash(stck_empt, pointers);	
	(pointers->sp)->dnumber = (double)((pointers->sp)->inumber);
}

//Convert double on TOS to int.
void static INLINE command_D2I(registers* pointers)
{
	if (pointers->sp < pointers->bottom) interpret_crash(stck_empt, pointers);	
	(pointers->sp)->inumber = (int)((pointers->sp)->dnumber);
}

//Convert string on TOS to int.
void static INLINE command_S2I(registers* pointers)
{
	if (pointers->sp < pointers->bottom) interpret_crash(stck_empt, pointers);
	(pointers->sp)->inumber = atoi(get_const((short)((pointers->sp)->str_id), pointers->pool));
}

//Swap 2 topmost values.
void static INLINE command_SWAP(registers* pointers)
{
	stack_t top;
	if ((pointers->sp - 1) < pointers->bottom) interpret_crash(stck_empt, pointers);
	top = *(pointers->sp);
	*(pointers->sp) = *(pointers->sp - 1);
	*(pointers->sp - 1) = top;
}

//Remove topmost value.
void static INLINE command_POP(registers* pointers)
{
	if (pointers->sp < pointers->bottom) interpret_crash(stck_empt, pointers);
	pointers->sp--;
}

//Load double from variable 0, push on TOS.
void static INLINE command_LOADDVAR0(registers* pointers)
{
	if (pointers->sp >= pointers->head) stack_realloc(pointers);
	pointers->sp++;
	(pointers->sp)->dnumber = pointers->ctxsp->locals->dnumber;
}

//Load double from variable 1, push on TOS.
void static INLINE command_LOADDVAR1(registers* pointers)
{
	if (pointers->sp >= pointers->head) stack_realloc(pointers);
	pointers->sp++;
	(pointers->sp)->dnumber = (pointers->ctxsp->locals + 1)->dnumber;
}

//Load double from variable 2, push on TOS.
void static INLINE command_LOADDVAR2(registers* pointers)
{
	if (pointers->sp >= pointers->head) stack_realloc(pointers);
	pointers->sp++;
	(pointers->sp)->dnumber = (pointers->ctxsp->locals + 2)->dnumber;
}

//Load double from variable 3, push on TOS.
void static INLINE command_LOADDVAR3(registers* pointers)
{
	if (pointers->sp >= pointers->head) stack_realloc(pointers);
	pointers->sp++;
	(pointers->sp)->dnumber = (pointers->ctxsp->locals + 3)->dnumber;
}

//Load int from variable 0, push on TOS.
void static INLINE command_LOADIVAR0(registers* pointers)
{
	if (pointers->sp >= pointers->head) stack_realloc(pointers);
	pointers->sp++;
	(pointers->sp)->inumber = pointers->ctxsp->locals->inumber;
}

//Load int from variable 1, push on TOS.
void static INLINE command_LOADIVAR1(registers* pointers)
{
	if (pointers->sp >= pointers->head) stack_realloc(pointers);
	pointers->sp++;
	(pointers->sp)->inumber = (pointers->ctxsp->locals + 1)->inumber;
}

//Load int from variable 2, push on TOS.
void static INLINE command_LOADIVAR2(registers* pointers)
{
	if (pointers->sp >= pointers->head) stack_realloc(pointers);
	pointers->sp++;
	(pointers->sp)->inumber = (pointers->ctxsp->locals + 2)->inumber;
}

//Load int from variable 3, push on TOS.
void static INLINE command_LOADIVAR3(registers* pointers)
{
	if (pointers->sp >= pointers->head) stack_realloc(pointers);
	pointers->sp++;
	(pointers->sp)->inumber = (pointers->ctxsp->locals + 3)->inumber;
}

//Load string from variable 0, push on TOS.
void static INLINE command_LOADSVAR0(registers* pointers)
{
	if (pointers->sp >= pointers->head) stack_realloc(pointers);
	pointers->sp++;
	(pointers->sp)->str_id = pointers->ctxsp->locals->str_id;
}

//Load string from variable 1, push on TOS.
void static INLINE command_LOADSVAR1(registers* pointers)
{
	if (pointers->sp >= pointers->head) stack_realloc(pointers);
	pointers->sp++;
	(pointers->sp)->str_id = (pointers->ctxsp->locals + 1)->str_id;
}

//Load string from variable 2, push on TOS.
void static INLINE command_LOADSVAR2(registers* pointers)
{
	if (pointers->sp >= pointers->head) stack_realloc(pointers);
	pointers->sp++;
	(pointers->sp)->str_id = (pointers->ctxsp->locals + 2)->str_id;
}

//Load string from variable 3, push on TOS.
void static INLINE command_LOADSVAR3(registers* pointers)
{
	if (pointers->sp >= pointers->head) stack_realloc(pointers);
	pointers->sp++;
	(pointers->sp)->str_id = (pointers->ctxsp->locals + 3)->str_id;
}

//Pop TOS and store to double variable 0.
void static INLINE command_STOREDVAR0(registers* pointers)
{
	if (pointers->sp < pointers->bottom) interpret_crash(stck_empt, pointers);
	pointers->sp--;
	pointers->ctxsp->locals->dnumber = (pointers->sp + 1)->dnumber;
}

//Pop TOS and store to double variable 1.
void static INLINE command_STOREDVAR1(registers* pointers)
{
	if (pointers->sp < pointers->bottom) interpret_crash(stck_empt, pointers);
	pointers->sp--;
	(pointers->ctxsp->locals + 1)->dnumber = (pointers->sp + 1)->dnumber;
}

//Pop TOS and store to double variable 2.
void static INLINE command_STOREDVAR2(registers* pointers)
{
	if (pointers->sp < pointers->bottom) interpret_crash(stck_empt, pointers);
	pointers->sp--;
	(pointers->ctxsp->locals + 2)->dnumber = (pointers->sp + 1)->dnumber;
}

//Pop TOS and store to double variable 3.
void static INLINE command_STOREDVAR3(registers* pointers)
{
	if (pointers->sp < pointers->bottom) interpret_crash(stck_empt, pointers);
	pointers->sp--;
	(pointers->ctxsp->locals + 3)->dnumber = (pointers->sp + 1)->dnumber;
}

//Pop TOS and store to int variable 0.
void static INLINE command_STOREIVAR0(registers* pointers)
{
	if (pointers->sp < pointers->bottom) interpret_crash(stck_empt, pointers);
	pointers->sp--;
	pointers->ctxsp->locals->inumber = (pointers->sp + 1)->inumber;
}

//Pop TOS and store to int variable 1.
void static INLINE command_STOREIVAR1(registers* pointers)
{
	if (pointers->sp < pointers->bottom) interpret_crash(stck_empt, pointers);
	pointers->sp--;
	(pointers->ctxsp->locals + 1)->inumber = (pointers->sp + 1)->inumber;
}

//Pop TOS and store to int variable 2.
void static INLINE command_STOREIVAR2(registers* pointers)
{
	if (pointers->sp < pointers->bottom) interpret_crash(stck_empt, pointers);
	pointers->sp--;
	(pointers->ctxsp->locals + 2)->inumber = (pointers->sp + 1)->inumber;
}

//Pop TOS and store to int variable 3.
void static INLINE command_STOREIVAR3(registers* pointers)
{
	if (pointers->sp < pointers->bottom) interpret_crash(stck_empt, pointers);
	pointers->sp--;
	(pointers->ctxsp->locals + 3)->inumber = (pointers->sp + 1)->inumber;
}

//Pop TOS and store to string variable 0.
void static INLINE command_STORESVAR0(registers* pointers)
{
	if (pointers->sp < pointers->bottom) interpret_crash(stck_empt, pointers);
	pointers->sp--;
	pointers->ctxsp->locals->str_id = (pointers->sp + 1)->str_id;
}

//Pop TOS and store to string variable 1.
void static INLINE command_STORESVAR1(registers* pointers)
{
	if (pointers->sp < pointers->bottom) interpret_crash(stck_empt, pointers);
	pointers->sp--;
	(pointers->ctxsp->locals + 1)->str_id = (pointers->sp + 1)->str_id;
}

//Pop TOS and store to string variable 2.
void static INLINE command_STORESVAR2(registers* pointers)
{
	if (pointers->sp < pointers->bottom) interpret_crash(stck_empt, pointers);
	pointers->sp--;
	(pointers->ctxsp->locals + 2)->str_id = (pointers->sp + 1)->str_id;
}

//Pop TOS and store to string variable 3.
void static INLINE command_STORESVAR3(registers* pointers)
{
	if (pointers->sp < pointers->bottom) interpret_crash(stck_empt, pointers);
	pointers->sp--;
	(pointers->ctxsp->locals + 3)->str_id = (pointers->sp + 1)->str_id;
}

//Load double from variable, whose 2-byte id is inlined to insn stream, push on TOS.
void static INLINE command_LOADDVAR(registers* pointers)
{
	if (pointers->sp >= pointers->head) stack_realloc(pointers);
	pointers->sp++;
	(pointers->sp)->dnumber = (pointers->ctxsp->locals + *((ushort*)(++pointers->ip)))->dnumber;
	pointers->ip++;
}

//Load int from variable, whose 2-byte id is inlined to insn stream, push on TOS.
void static INLINE command_LOADIVAR(registers* pointers)
{
	if (pointers->sp >= pointers->head) stack_realloc(pointers);
	pointers->sp++;
	(pointers->sp)->inumber = (pointers->ctxsp->locals + *((ushort*)(++pointers->ip)))->inumber;
	pointers->ip++;
}

//Load string from variable, whose 2-byte id is inlined to insn stream, push on TOS.
void static INLINE command_LOADSVAR(registers* pointers)
{
	if (pointers->sp >= pointers->head) stack_realloc(pointers);
	pointers->sp++;
	(pointers->sp)->str_id = (pointers->ctxsp->locals + *((ushort*)(++pointers->ip)))->str_id;
	pointers->ip++;
}

//Pop TOS and store to double variable, whose 2-byte id is inlined to insn stream.
void static INLINE command_STOREDVAR(registers* pointers)
{
	if (pointers->sp < pointers->bottom) interpret_crash(stck_empt, pointers);
	pointers->sp--;
	(pointers->ctxsp->locals + *((ushort*)(++pointers->ip)))->dnumber = (pointers->sp + 1)->dnumber;
	pointers->ip++;
}

//Pop TOS and store to int variable, whose 2-byte id is inlined to insn stream.
void static INLINE command_STOREIVAR(registers* pointers)
{
	if (pointers->sp < pointers->bottom) interpret_crash(stck_empt, pointers);
	pointers->sp--;
	(pointers->ctxsp->locals + *((ushort*)(++pointers->ip)))->inumber = (pointers->sp + 1)->inumber;
	pointers->ip++;
}

//Pop TOS and store to string variable, whose 2-byte id is inlined to insn stream.
void static INLINE command_STORESVAR(registers* pointers)
{
	if (pointers->sp < pointers->bottom) interpret_crash(stck_empt, pointers);
	pointers->sp--;
	(pointers->ctxsp->locals + *((ushort*)(++pointers->ip)))->str_id = (pointers->sp + 1)->str_id;
	pointers->ip++;
}

//Load double from variable, whose 2-byte context and 2-byte id inlined to insn stream, push on TOS.
void static INLINE command_LOADCTXDVAR(registers* pointers)
{
	/*int del;
	function_table* func;
	if (pointers->sp >= pointers->head) stack_realloc(pointers);
	pointers->sp++;
	func = get_function(pointers->table, *((ushort*)(++pointers->ip)), pointers->count_functions);
	if (func == NULL || func->ctx_count == 0) interpret_crash(ctx_empt, pointers);
	pointers->ip++;
	if (func->id == pointers->current_function->id) del = 2;
	else del = 1;
	(pointers->sp)->dnumber = ((func->ctx + func->ctx_count - del)->locals + *((ushort*)(++pointers->ip)))->dnumber;
	pointers->ip++;*/
}

//Load int from variable, whose 2-byte context and 2-byte id inlined to insn stream, push on TOS.
void static INLINE command_LOADCTXIVAR(registers* pointers)
{
	/*int del;
	function_table* func;
	if (pointers->sp >= pointers->head) stack_realloc(pointers);
	pointers->sp++;
	func = get_function(pointers->table, *((ushort*)(++pointers->ip)), pointers->count_functions);
	if (func == NULL || func->ctx_count == 0) interpret_crash(ctx_empt, pointers);
	pointers->ip++;
	if (func->id == pointers->current_function->id) del = 2;
	else del = 1;
	(pointers->sp)->inumber = ((func->ctx + func->ctx_count - del)->locals + *((ushort*)(++pointers->ip)))->inumber;
	pointers->ip++;*/
}

//Load string from variable, whose 2-byte context and 2-byte id inlined to insn stream, push on TOS.
void static INLINE command_LOADCTXSVAR(registers* pointers)
{
	/*int del;
	function_table* func;
	if (pointers->sp >= pointers->head) stack_realloc(pointers);
	pointers->sp++;
	func = get_function(pointers->table, *((ushort*)(++pointers->ip)), pointers->count_functions);
	if (func == NULL || func->ctx_count == 0) interpret_crash(ctx_empt, pointers);
	pointers->ip++;
	if (func->id == pointers->current_function->id) del = 2;
	else del = 1;
	(pointers->sp)->str_id = ((func->ctx + func->ctx_count - del)->locals + *((ushort*)(++pointers->ip)))->str_id;
	pointers->ip++;*/
}

//Pop TOS and store to double variable, whose 2-byte context and 2-byte id is inlined to insn stream.
void static INLINE command_STORECTXDVAR(registers* pointers)
{
	/*int del;
	function_table* func;
	if (pointers->sp < pointers->bottom) interpret_crash(stck_empt, pointers);
	pointers->sp--;
	func = get_function(pointers->table, *((ushort*)(++pointers->ip)), pointers->count_functions);
	if (func == NULL || func->ctx_count == 0) interpret_crash(ctx_empt, pointers);
	pointers->ip++;
	if (func->id == pointers->current_function->id) del = 2;
	else del = 1;
	((func->ctx + func->ctx_count - del)->locals + *((ushort*)(++pointers->ip)))->dnumber = (pointers->sp + 1)->dnumber;
	pointers->ip++;*/
}

//Pop TOS and store to int variable, whose 2-byte context and 2-byte id is inlined to insn stream.
void static INLINE command_STORECTXIVAR(registers* pointers)
{
	/*int del;
	function_table* func;
	if (pointers->sp < pointers->bottom) interpret_crash(stck_empt, pointers);
	pointers->sp--;
	func = get_function(pointers->table, *((ushort*)(++pointers->ip)), pointers->count_functions);
	if (func == NULL || func->ctx_count == 0) interpret_crash(ctx_empt, pointers);
	pointers->ip++;
	if (func->id == pointers->current_function->id) del = 2;
	else del = 1;
	((func->ctx + func->ctx_count - del)->locals + *((ushort*)(++pointers->ip)))->inumber = (pointers->sp + 1)->inumber;
	pointers->ip++;*/
}

//Pop TOS and store to string variable, whose 2-byte context and 2-byte id is inlined to insn stream.
void static INLINE command_STORECTXSVAR(registers* pointers)
{
	/*int del;
	function_table* func;
	if (pointers->sp < pointers->bottom) interpret_crash(stck_empt, pointers);
	pointers->sp--;
	func = get_function(pointers->table, *((ushort*)(++pointers->ip)), pointers->count_functions);
	if (func == NULL || func->ctx_count == 0) interpret_crash(ctx_empt, pointers);
	pointers->ip++;
	if (func->id == pointers->current_function->id) del = 2;
	else del = 1;
	((func->ctx + func->ctx_count - del)->locals + *((ushort*)(++pointers->ip)))->str_id = (pointers->sp + 1)->str_id;
	pointers->ip++;*/
}

//Compare 2 topmost doubles, pushing libc-style comparator value cmp(upper, lower) as integer.
void static INLINE command_DCMP(registers* pointers)
{
	if ((pointers->sp - 1) < pointers->bottom) interpret_crash(stck_empt, pointers);
	if ((pointers->sp)->dnumber > (pointers->sp - 1)->dnumber) command_DLOAD1(pointers);
	else if ((pointers->sp)->dnumber < (pointers->sp - 1)->dnumber) command_DLOADM1(pointers);
	else command_DLOAD0(pointers);
}

//Compare 2 topmost ints, pushing libc-style comparator value cmp(upper, lower) as integer.
void static INLINE command_ICMP(registers* pointers)
{
	if ((pointers->sp - 1) < pointers->bottom) interpret_crash(stck_empt, pointers);
	if ((pointers->sp)->inumber > (pointers->sp - 1)->inumber) command_ILOAD1(pointers);
	else if ((pointers->sp)->inumber < (pointers->sp - 1)->inumber) command_ILOADM1(pointers);
	else command_ILOAD0(pointers);
}

//Jump always, next two bytes - signed sp of jump destination.
void static INLINE command_JA(registers* pointers)
{
	pointers->ip += *((short*)(++pointers->ip)) + 1;
}

//Compare two topmost integers and jump if upper != lower, next two bytes - signed sp of jump destination.
void static INLINE command_IFICMPNE(registers* pointers)
{
	if ((pointers->sp - 1) < pointers->bottom) interpret_crash(stck_empt, pointers);
	if ((pointers->sp)->inumber != (pointers->sp - 1)->inumber) command_JA(pointers);
	else pointers->ip += sizeof(short);
}

//Compare two topmost integers and jump if upper == lower, next two bytes - signed sp of jump destination.
void static INLINE command_IFICMPE(registers* pointers)
{
	if ((pointers->sp - 1) < pointers->bottom) interpret_crash(stck_empt, pointers);
	if ((pointers->sp)->inumber == (pointers->sp - 1)->inumber) command_JA(pointers);
	else pointers->ip += sizeof(short);
}

//Compare two topmost integers and jump if upper > lower, next two bytes - signed sp of jump destination.
void static INLINE command_IFICMPG(registers* pointers)
{
	if ((pointers->sp - 1) < pointers->bottom) interpret_crash(stck_empt, pointers);
	if ((pointers->sp)->inumber > (pointers->sp - 1)->inumber) command_JA(pointers);
	else pointers->ip += sizeof(short);
}

//Compare two topmost integers and jump if upper >= lower, next two bytes - signed sp of jump destination.
void static INLINE command_IFICMPGE(registers* pointers)
{
	if ((pointers->sp - 1) < pointers->bottom) interpret_crash(stck_empt, pointers);
	if ((pointers->sp)->inumber >= (pointers->sp - 1)->inumber) command_JA(pointers);
	else pointers->ip += sizeof(short);
}

//Compare two topmost integers and jump if upper < lower, next two bytes - signed sp of jump destination.
void static INLINE command_IFICMPL(registers* pointers)
{
	if ((pointers->sp - 1) < pointers->bottom) interpret_crash(stck_empt, pointers);
	if ((pointers->sp)->inumber < (pointers->sp - 1)->inumber) command_JA(pointers);
	else pointers->ip += sizeof(short);
}

//Compare two topmost integers and jump if upper <= lower, next two bytes - signed sp of jump destination.
void static INLINE command_IFICMPLE(registers* pointers)
{
	if ((pointers->sp - 1) < pointers->bottom) interpret_crash(stck_empt, pointers);
	if ((pointers->sp)->inumber <= (pointers->sp - 1)->inumber) command_JA(pointers);
	else pointers->ip += sizeof(short);
}

//Dump value on TOS, without removing it.
void static INLINE command_DUMP(registers* pointers)
{
	if (!(pointers->sp < pointers->bottom)) 
		printf("Int %lld\nDouble %f\nStringId %lld\n", (pointers->sp)->inumber, 
		(pointers->sp)->dnumber, (pointers->sp)->str_id);
}

//Stop execution.
void static INLINE command_STOP(registers* pointers)
{
	//Unused.
	interpret_crash(stp_commnd, pointers);
}

//Call function, next two bytes - unsigned function id.
void static INLINE command_CALL(registers* pointers)
{
	 uint i;
	 context_t *prev_context;
	 function_table* prev_function = pointers->current_function;
	 pointers->ctxsp++;
	 if (pointers->ctxsp >= pointers->ctx_bottom + FRAMES) interpret_crash(ctx_overflow, pointers);
	 pointers->current_function = get_function(pointers->table, *((ushort*)(++pointers->ip)), pointers->count_functions);
	 prev_context = pointers->current_function->ctx;
	 pointers->current_function->ctx = pointers->ctxsp;
	 pointers->ctxsp->previous_ctx = prev_context;
	 pointers->ctxsp->previous_function = prev_function;
	 pointers->ctxsp->return_address = ++pointers->ip;
	 pointers->ctxsp->locals = (stack_t*)malloc(sizeof(stack_t) * pointers->current_function->locals);
	 if ((pointers->sp + 2 - pointers->current_function->args) <= pointers->bottom) interpret_crash(stck_empt, pointers);
	 for (i = 0; i < pointers->current_function->args; i++)
		 *(pointers->ctxsp->locals + i) = *(pointers->sp - i);
	 pointers->sp -= pointers->current_function->args;
	 pointers->ip = pointers->byte_code + (pointers->current_function->offset) - 1;
}

//Call native function, next two bytes - id of the native function.
void static INLINE command_CALLNATIVE(registers* pointers)
{
	//Something wonderfull and beautiful.
}

//Return to call location.
void static INLINE command_RETURN(registers* pointers)
{
	if (pointers->ctxsp->previous_function == NULL || pointers->ctxsp->return_address == NULL || pointers->ctxsp == pointers->ctx_bottom) interpret_crash(ctx_empt, pointers);
	pointers->ip = pointers->ctxsp->return_address;
	free(pointers->ctxsp->locals);
	pointers->current_function->ctx = pointers->ctxsp->previous_ctx;
	pointers->current_function = pointers->ctxsp->previous_function;
	pointers->ctxsp--;
}

//Breakpoint for the debugger.
void static INLINE command_BREAK(registers* pointers)
{
	//Something, that can help.
}

/*End of Instructions*/


//Interpeter body. Really.
int interpreter(registers* pointers)
{
	//Initialization of calculation stack.
	pointers->bottom = (stack_t*)malloc(sizeof(stack_t) * START_SIZE);
	pointers->head = pointers->bottom + START_SIZE;
	pointers->sp = pointers->bottom + ZERO_OFFSET;
	//VERY BIG SWITCH! VERY. BIG.
	while (TRUE)
	{
		switch(*pointers->ip)
		{
			#define CASE(code, l) case code : command_##code (pointers); break;
				FOR_BYTECODES( CASE )
			case STOP: registers_destruction(pointers); return stp_commnd;
			default: command_INVALID(pointers);
		}
		pointers->ip++;
	}
}

//If interpreting was failed... do it.
void interpret_crash(int err_code, registers* pointers)
{
	registers_destruction(pointers);
	program_crash(err_code);
}

//Destroying of all registers. Memory must be free.
void registers_destruction(registers* pointers)
{
	uint i;
	free(pointers->bottom);
	free(pointers->ctxsp->locals);
	free(pointers->ctx_bottom);
	/*for (i = 0; i < pointers->count_functions; i++)
		free((pointers->table + i)->ctx);*/
	free(pointers->table);
	free(pointers->byte_code);
	pool_destroy(pointers->pool);
	free(pointers);
}