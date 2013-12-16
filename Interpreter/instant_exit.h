

//Codes of errors and their names comparision.
typedef enum 
{
	inval_instr = 1,
	stck_overflow,
	stck_empt,


	stp_commnd = 6109,
}error_codes;

void interpret_crash(int error_code);