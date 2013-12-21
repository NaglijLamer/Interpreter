#ifndef COMMANDS_H_
#define COMMANDS_H_

#define FOR_BYTECODES(DO)	\
        DO(INVALID, 1)      \
        DO(DLOAD, 9)		\
        DO(ILOAD, 9)		\
        DO(SLOAD, 3)		\
        DO(DLOAD0, 1)       \
        DO(ILOAD0,  1)      \
        DO(SLOAD0, 1)       \
        DO(DLOAD1, 1)       \
        DO(ILOAD1, 1)       \
        DO(DLOADM1, 1)      \
        DO(ILOADM1, 1)      \
        DO(DADD, 1)         \
        DO(IADD, 1)         \
        DO(DSUB, 1)			\
        DO(ISUB, 1)			\
        DO(DMUL, 1)			\
        DO(IMUL, 1)         \
        DO(DDIV, 1)			\
        DO(IDIV, 1)			\
        DO(IMOD, 1)			\
        DO(DNEG, 1)         \
        DO(INEG, 1)         \
        DO(IPRINT, 1)       \
        DO(DPRINT, 1)       \
        DO(SPRINT, 1)       \
        DO(I2D, 1)          \
        DO(D2I, 1)          \
        DO(S2I, 1)          \
        DO(SWAP, 1)         \
        DO(POP, 1)          \
        DO(LOADDVAR0, 1)	\
        DO(LOADDVAR1, 1)	\
        DO(LOADDVAR2, 1)	\
        DO(LOADDVAR3, 1)	\
        DO(LOADIVAR0, 1)    \
        DO(LOADIVAR1, 1)    \
        DO(LOADIVAR2, 1)    \
        DO(LOADIVAR3, 1)    \
        DO(LOADSVAR0, 1)	\
        DO(LOADSVAR1, 1)	\
        DO(LOADSVAR2, 1)	\
        DO(LOADSVAR3, 1)	\
        DO(STOREDVAR0, 1)   \
        DO(STOREDVAR1, 1)   \
        DO(STOREDVAR2, 1)   \
        DO(STOREDVAR3, 1)   \
        DO(STOREIVAR0, 1)   \
        DO(STOREIVAR1, 1)   \
        DO(STOREIVAR2, 1)   \
        DO(STOREIVAR3, 1)   \
        DO(STORESVAR0, 1)   \
        DO(STORESVAR1, 1)   \
        DO(STORESVAR2, 1)   \
        DO(STORESVAR3, 1)   \
        DO(LOADDVAR, 3)		\
        DO(LOADIVAR, 3)		\
        DO(LOADSVAR, 3)		\
        DO(STOREDVAR, 3)	\
        DO(STOREIVAR, 3)	\
        DO(STORESVAR, 3)	\
        DO(LOADCTXDVAR, 5)	\
        DO(LOADCTXIVAR, 5)	\
        DO(LOADCTXSVAR, 5)	\
        DO(STORECTXDVAR, 5) \
        DO(STORECTXIVAR, 5) \
        DO(STORECTXSVAR, 5) \
        DO(DCMP, 1)			\
        DO(ICMP, 1)			\
        DO(JA, 3)			\
        DO(IFICMPNE, 3)		\
        DO(IFICMPE, 3)		\
        DO(IFICMPG, 3)		\
        DO(IFICMPGE, 3)		\
        DO(IFICMPL, 3)		\
        DO(IFICMPLE, 3)		\
        DO(DUMP, 1)			\
        DO(CALL, 3)			\
        DO(CALLNATIVE, 3)	\
        DO(RETURN, 1)		\
        DO(BREAK, 1)		

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

#endif