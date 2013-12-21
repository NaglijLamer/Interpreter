#ifndef PARSER_H_
#define PARSER_H_

#include "interpreter.h"

registers parser_file(FILE* program);

typedef struct{
	ushort signature;
	ushort version;
	uint count_constant;
	uint size_of_constant;
	uint size_of_file;
	uint entry_point_id;
	uint count_function;
}file_header;

typedef struct{
	ushort id;
	uint size_of_function;
	uint size_of_byte_code;
	ushort size_of_arguments;
	ushort size_of_locals;
}function_header;

#endif