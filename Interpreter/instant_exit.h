#ifndef EXIT_H_
#define EXIT_H_

//Codes of errors and their names comparision.
typedef enum 
{
	inval_instr = 1,
	stck_overflow,
	stck_empt,
	wrng_file,

	stp_commnd = 6109,
}error_codes;

void interpret_crash(int error_code);

#endif