//File with arrays for string constants.
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdlib.h>
#include <string.h>
#define SIZE 65535

char* get_const(short id, char** pool)
{
	return *(pool + id);
}

void add_const(short id, char** pool, char* value)
{
	*(pool + id) = (char*)malloc(strlen(value) + 1);
	strcpy(*(pool + id), value);
}

char** pool_create()
{
	char** pool = (char**)calloc(SIZE, sizeof(char*));
	add_const(0, pool, "");
	//*(pool + 0) = "";
	return pool;
}

void pool_destroy(char** pool)
{
	int i = 0;
	while(*(pool + i))
		free(*(pool + i++));
	free(pool);
}