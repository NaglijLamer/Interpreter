//File with arrays for string constants.
#include <stdlib.h>
#define SIZE 65535

char** pool_create()
{
	char** pool = (char**)malloc(SIZE * sizeof(char*));
	*pool = "";
	return pool;
}

char* get_const(short id, char** pool)
{
	return *(pool + id);
}

void add_const(short id, char** pool, char* value)
{
	*(pool + id) = value;
}

void pool_destroy(char** pool)
{
	free(pool);
}