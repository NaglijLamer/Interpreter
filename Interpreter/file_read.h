

typedef struct{
	unsigned int signature;
	double version;
	unsigned int constants;
	unsigned int size_of_file;
	unsigned int entry_point_id;
	unsigned int functions;
}file_header;

typedef struct{
	unsigned int size;
	unsigned int size_of_byte-code;
	//some question about function format...
}function;