#ifndef EXIT_H_
#define EXIT_H_

//Codes of errors and their names comparision.
typedef enum 
{
	inval_instr = 1,
	stck_overflow,
	stck_empt,
	wrng_file,
	ctx_empt,
	ctx_overflow,
	no_entr_funct,

	unknwn = 404,
	stp_commnd = 6109,
}error_codes;

//Crash'em all.
void program_crash(int error_code);

#endif