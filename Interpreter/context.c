#include "context.h"

function_table* get_function(function_table* table, unsigned short id, int function_count)
{
	int i;
	for (i = 0; i <= function_count; i++)
		if (id == (table + i)->id) return (table + i);
	return NULL;
}
