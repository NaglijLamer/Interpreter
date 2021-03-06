#ifndef PARSER_H_
#define PARSER_H_

#pragma pack(push,1)
#include "interpreter.h"

//Main parser function.
registers* parser_file(FILE* program);

//Structs for function and file headers.
typedef struct{
	ushort signature;
	uint version;
	uint count_constant;
	uint size_of_constant;
}file_header1;

typedef struct{
	ushort entry_point_id;
	uint count_function;
}file_header2;

typedef struct{
	uint size_of_function;
	uint size_of_byte_code;
	uint size_of_sign;
}function_header1;

typedef struct{
	ushort id;
	uint count_of_locals;
	uint count_of_arguments;
}function_header2;

#pragma pack(pop)
#endif