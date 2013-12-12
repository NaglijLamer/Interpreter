

typedef union 
{
	long long inumber;
	double dnumber;
	char* str;
}string_t;

typedef struct stack_t stack_t;
struct stack_t
{
	string_t* value;
	stack_t* next;
};

void push(stack_t** stackp, string_t* value);
string_t* pop(stack_t** stackp);