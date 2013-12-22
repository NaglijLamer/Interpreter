//File with arrays for string constants.

#include <stdlib.h>
#include <string.h>
#define SIZE 65535

char** pool_create()
{
	char** pool = (char**)calloc(SIZE, sizeof(char*));
	*pool = "";
	return pool;
}

char* get_const(short id, char** pool)
{
	return *(pool + id);
}

void add_const(short id, char** pool, char* value)
{
	*(pool + id) = (char*)malloc(strlen(value));
	strcpy(*(pool + id), value);
}

void pool_destroy(char** pool)
{
	int i = 0;
	while(*(pool + i))
		free(*(pool + i++));
	free(pool);
}