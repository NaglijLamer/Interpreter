//File with functions and enums for working with exit_codes.

#include <stdlib.h>
#include <stdio.h>
#include "instant_exit.h"

//Crash program, if we habe troubles.
void program_crash(int error_code)
{
	switch(error_code)
	{
		case inval_instr: fputs("Error! Invalid instruction.", stderr); break;
		case stck_overflow: fputs("Error! Stack overflow", stderr); break;
		case stck_empt: fputs("Error! Stack is empty or not enough arguments!", stderr); break;
		case wrng_file: fputs("Error! There is not an executable file!", stderr); break;
		case ctx_empt: fputs("Error! The appeal to a context which doesn't exist or context is broken!", stderr); break;
		case ctx_overflow: fputs("Error! Too many frames for one function!", stderr); break;
		case no_entr_funct: fputs("Error! Can not find an entry point!", stderr); break;
		case wrng_fname: fputs("Error! Can't open or find this file!", stderr); break;
		case usage: fputs("Usage: interpreter filename", stderr); break;

		case unknwn: fputs("Unknown error! It is used only for tests and debug.", stderr); break;
		case stp_commnd: fputs("Execution was stopped by command!", stderr); break;
	}
	
	exit(error_code);
}