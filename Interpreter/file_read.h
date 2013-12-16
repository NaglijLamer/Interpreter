

typedef char* function;
typedef function* functions;
typedef unsigned int uint;

typedef struct{
	uint signature;
	uint main_version;
	char* dot;
	uint second_version;
	uint constants;
	uint size_of_file;
	uint entry_point_id;
	uint functions;
}file_header;

typedef struct{
	uint size;
	uint size_of_byte_code;
	//some question about function format...
}function_header;

