//File with functions and enums for working with exit_codes.

#include <stdlib.h>
#include <stdio.h>
#include "instant_exit.h"

//Crash program, if we habe troubles with stack.
void interpret_crash(int error_code)
{
	switch(error_code)
	{
		case inval_instr: fputs("Error! Invalid instruction.", stderr); break;
		case stck_overflow: fputs("Error! Stack overflow", stderr); break;
		case stck_empt: fputs("Error! Stack is empty or not enough arguments!", stderr); break;
		case wrng_file: fputs("Error! There is not an executable file!", stderr); break;
		case ctx_empt: fputs("Error! The appeal to a context which doesn't exist!", stderr); break;

		case stp_commnd: fputs("Execution was stopped by command!", stderr); break;
	}
	
	exit(error_code);
}