
#include "instant_exit.h"
#include "file_read.h"

//Element in stack.
typedef union 
{
	long long inumber;
	double dnumber;
	long long str_id;
}stack_t;

//Stack.
typedef struct
{
	stack_t* bottom;	//Bottom of stack,
	stack_t* sp;		//Stack Pointer.
	stack_t* head;		//= bottom + head = maxSP.
	function ip;		//Instruction Pointer.
						//May be a pointer for a constant pool.
}registers;

//Codes and commands comparison.
typedef enum
{
	INVALID = 0x00,
	DLOAD = 0x01, ILOAD, SLOAD, DLOAD0, ILOAD0, SLOAD0, DLOAD1, ILOAD1, DLOADM1, ILOADM1,
	DADD = 0x0B, IADD, DSUB, ISUB, DMUL, IMUL, DDIV, IDIV, IMOD, DNEG, INEG,
	IPRINT = 0x16, DPRINT, SPRINT, 
	I2D = 0x19, D2I, S2I,
	SWAP = 0x1C, POP = 0x1D,
	LOADDVAR0 = 0x1E, LOADDVAR1, LOADDVAR2, LOADDVAR3, LOADIVAR0, LOADIVAR1, LOADIVAR2, LOADIVAR3, LOADSVAR0, LOADSVAR1, LOADSVAR2, LOADSVAR3,
	STOREDVAR0 = 0x2A, STOREDVAR1, STOREDVAR2, STOREDVAR3, STOREIVAR0, STOREIVAR1, STOREIVAR2, STOREIVAR3, STORESVAR0, STORESVAR1, STORESVAR2, STORESVAR3,
	LOADDVAR = 0x36, LOADIVAR, LOADSVAR,
	STOREDVAR = 0x39, STOREIVAR, STORESVAR,
	LOADCTXDVAR = 0x3C, LOADCTXIVAR, LOADCTXSVAR,
	STORECTXDVAR = 0x3F, STORECTXIVAR, STORECTXSVAR,
	DCMP = 0x42, ICMP,
	JA = 0x44,
	IFICMPNE = 0x45, IFICMPE, IFICMPG, IFICMPGE, IFICMPL, IFICMPLE,
	DUMP = 0x4B,
	STOP = 0x4C,
	CALL = 0x4D, CALLNATIVE, RETURN,
	BREAK = 0x50,
}commands;

int interpreter(functions byte_code, uint entry_point_id, uint size_of_byte_code);
void stack_destruction(registers* pointers);