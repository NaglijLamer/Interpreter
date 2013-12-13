//File with realization of bytecode commands.

#include <stdio.h>
#include <stdlib.h>
#include "interpreter.h"

//Invalid instruction.
void command_INVALID()
{
	fputs("Error! Invalid instruction.", stderr);
	//Create enum with exit_codes!!!
	exit(1); 
}

//Load double on TOS, inlined into insn stream.
void command_DLOAD(stack_t** stackp, double d)
{
	string_t* value = (string_t*)malloc(sizeof(string_t));
	value->dnumber = d;
	push(stackp, value);
}

//Load int on TOS, inlined into insn stream.
void command_ILOAD(stack_t** stackp, int i)
{
	string_t* value = (string_t*)malloc(sizeof(string_t));
	value->inumber = i;
	push(stackp, value);
}

//Load string reference on TOS, next two bytes - constant id.
void command_SLOAD(stack_t** stackp, char* s)
{
	string_t* value = (string_t*)malloc(sizeof(string_t));
	value->str = s;
	push(stackp, value);
}

//Load double 0 on TOS.
void command_DLOAD0(stack_t** stackp)
{
	command_DLOAD(stackp, 0.0);
}

//Load int 0 on TOS.
void command_ILOAD0(stack_t** stackp)
{
	command_ILOAD(stackp, 0);
}

//Load empty string on TOS.
/* !!! Empty string?? !!! */
void command_SLOAD0(stack_t** stackp)
{
	command_SLOAD(stackp, NULL);
}

//Load double 1 on TOS.
void command_DLOAD1(stack_t** stackp)
{
	command_DLOAD(stackp, 1.0);
}

//Load int 1 on TOS.
void command_ILOAD1(stack_t** stackp)
{
	command_ILOAD(stackp, 1);
}

//Load double -1 on TOS.
void command_DLOADM1(stack_t** stackp)
{
	command_DLOAD(stackp, -1.0);
}

//Load int -1 on TOS.
void command_ILOADM(stack_t** stackp)
{
	command_ILOAD(stackp, -1);
}

//Add 2 doubles on TOS, push value back.
void command_DADD(stack_t** stackp)
{
	string_t *add1, *add2, *sum;
	add1 = pop(stackp);
	add2 = pop(stackp);
	sum = (string_t*)malloc(sizeof(string_t));
	sum->dnumber = add1->dnumber + add2->dnumber;
	free(add1);
	free(add2);
	push(stackp, sum);
}

//Add 2 ints on TOS, push value back.
void command_IADD(stack_t** stackp)
{
	string_t *add1, *add2, *sum;
	add1 = pop(stackp);
	add2 = pop(stackp);
	sum = (string_t*)malloc(sizeof(string_t));
	sum->inumber = add1->inumber + add2->inumber;
	free(add1);
	free(add2);
	push(stackp, sum);
}

//Subtract 2 doubles on TOS (lower from upper), push value back.
void command_DSUB(stack_t** stackp)
{
	string_t *minuend , *subtrahend, *sub;
	minuend = pop(stackp);
	subtrahend = pop(stackp);
	sub = (string_t*)malloc(sizeof(string_t));
	sub->dnumber = minuend->dnumber - subtrahend->dnumber;
	free(minuend);
	free(subtrahend);
	push(stackp, sub);
}

//Subtract 2 ints on TOS (lower from upper), push value back.
void command_ISUB(stack_t** stackp)
{
	string_t *minuend , *subtrahend, *sub;
	minuend = pop(stackp);
	subtrahend = pop(stackp);
	sub = (string_t*)malloc(sizeof(string_t));
	sub->inumber = minuend->inumber - subtrahend->inumber;
	free(minuend);
	free(subtrahend);
	push(stackp, sub);
}

//Multiply 2 doubles on TOS, push value back.
void command_DMUL(stack_t** stackp)
{
	string_t *mult1 , *mult2, *prod;
	mult1 = pop(stackp);
	mult2 = pop(stackp);
	prod = (string_t*)malloc(sizeof(string_t));
	prod->dnumber = mult1->dnumber * mult2->dnumber;
	free(mult1);
	free(mult2);
	push(stackp, prod);
}

//Multiply 2 ints on TOS, push value back.
void command_IMUL(stack_t** stackp)
{
	string_t *mult1 , *mult2, *prod;
	mult1 = pop(stackp);
	mult2 = pop(stackp);
	prod = (string_t*)malloc(sizeof(string_t));
	prod->inumber = mult1->inumber * mult2->inumber;
	free(mult1);
	free(mult2);
	push(stackp, prod);
}

//Divide 2 doubles on TOS (upper to lower), push value back.
void command_DDIV(stack_t** stackp)
{
	string_t *dividend , *divisor, *quotient;
	dividend = pop(stackp);
	divisor = pop(stackp);
	quotient = (string_t*)malloc(sizeof(string_t));
	quotient->dnumber = dividend->dnumber / divisor->dnumber;
	free(dividend);
	free(divisor);
	push(stackp, quotient);
}

//Divide 2 ints on TOS (upper to lower), push value back.
void command_IDIV(stack_t** stackp)
{
	string_t *dividend , *divisor, *quotient;
	dividend = pop(stackp);
	divisor = pop(stackp);
	quotient = (string_t*)malloc(sizeof(string_t));
	quotient->inumber = dividend->inumber / divisor->inumber;
	free(dividend);
	free(divisor);
	push(stackp, quotient);
}

//Modulo operation on 2 ints on TOS (upper to lower), push value back.
void command_IMOD(stack_t** stackp)
{
	string_t *dividend , *divisor, *modulo;
	dividend = pop(stackp);
	divisor = pop(stackp);
	modulo = (string_t*)malloc(sizeof(string_t));
	modulo->inumber = dividend->inumber % divisor->inumber;
	free(dividend);
	free(divisor);
	push(stackp, modulo);
}

//Negate double on TOS.
void command_DNEG(stack_t** stackp)
{
	string_t *d;
	d = pop(stackp);
	d->dnumber = -(d->dnumber);
	push(stackp, d);
}

//Negate int on TOS.
void command_INEG(stack_t** stackp)
{
	string_t *i;
	i = pop(stackp);
	i->inumber = -(i->inumber);
	push(stackp, i);
}

//Pop and print integer TOS.
void command_IPRINT(stack_t** stackp)
{
	printf("%d\n", pop(stackp)->inumber);
}

//Pop and print double TOS.
void command_DPRINT(stack_t** stackp)
{
	printf("%f\n", pop(stackp)->dnumber);
}

//Pop and print string TOS.
void command_SPRINT(stack_t** stackp)
{
	printf("%s\n", *(pop(stackp)->str));
}

//Convert int on TOS to double.
void command_I2D(stack_t** stackp)
{
	string_t* i = pop(stackp);
	i->dnumber = (double)(i->inumber);
	push(stackp, i);
}

//Convert double on TOS to int.
void command_D2I(stack_t** stackp)
{
	string_t* d = pop(stackp);
	d->inumber = (int)(d->dnumber);
	push(stackp, d);
}

//Convert string on TOS to int.
void command_S2I(stack_t** stackp)
{
	string_t* ch = pop(stackp);
	//I don't know, what this command should do.
}

//Swap 2 topmost values.
void command_SWAP(stack_t** stackp)
{
	string_t *first , *second;
	first = pop(stackp);
	second = pop(stackp);
	push(stackp, second);
	push(stackp, first);
}

//Remove topmost value.
void command_POP(stack_t** stackp)
{
	pop(stackp);
}

/*	Commands, that can works woth variables.	*/

//Compare 2 topmost doubles, pushing libc-stryle comparator value cmp(upper, lower) as integer.
void command_DCMP(stack_t** stackp)
{
	string_t *d1, *d2, *value;
	d1 = pop(stackp);
	d2 = pop(stackp);
	push(stackp, d2);
	push(stackp, d1);
	value = (string_t*)malloc(sizeof(string_t));
	if (d1 > d2) value->inumber = 1;
	else if (d2 > d1) value->inumber = -1;
	else value->inumber = 0;
	push(stackp, value);
}

//Compare 2 topmost ints, pushing libc-style comparator value cmp(upper, lower) as integer.
void command_ICMP(stack_t** stackp)
{
	string_t *i1, *i2, *value;
	i1 = pop(stackp);
	i2 = pop(stackp);
	push(stackp, i2);
	push(stackp, i1);
	value = (string_t*)malloc(sizeof(string_t));
	if (i1 > i2) value->inumber = 1;
	else if (i2 > i1) value->inumber = -1;
	else value->inumber = 0;
	push(stackp, value);
}

/*	Commands, that can compare and jump.	*/

//Dump value on TOS, without removing it.
void command_DUMP(stack_t** stackp)
{
	string_t* value = pop(stackp);
	push(stackp, value);
	printf("Int %d\nDouble %f\nString %s\n", pop(stackp)->inumber, pop(stackp)->dnumber, *(pop(stackp)->str));
}

//Stop execution.
void command_STOP()
{
	fputs("Execution was stopped by command!", stderr);
	exit(6109);
}

/*	Commands, that can call functions and return from them.	*/
/*	Command, that can debug it.	*/