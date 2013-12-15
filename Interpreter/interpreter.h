

typedef union 
{
	long long inumber;
	double dnumber;
	char* str;
}stack_t;

typedef struct
{
	stack_t* bottom;
	size_t offset;
	size_t size_of_stack;
}current_stack_t;
