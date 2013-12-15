//File with functions and enums for working with exit_codes.

#include <stdlib.h>
#include <stdio.h>
#include "instant_exit.h"

//Crash program, if we habe troubles with stack.
void interpret_crash(int error_code)
{
	//I need error_enum. Really,
	switch(error_code)
	{
		case inval_instr: fputs("Error! Invalid instruction.", stderr); break;
		case stck_overflow: fputs("Error! Stack overflow", stderr); break;
		case stck_empt: fputs("Error! Stack is empty or not enough arguments!", stderr); break;


		case stp_commnd: fputs("Execution was stopped by command!", stderr); break;
	}
	exit(error_code);
}