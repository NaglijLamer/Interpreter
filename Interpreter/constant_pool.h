#ifndef POOL_H_
#define POOL_H_

char** pool_create();
char* get_const(short id, char** pool);
void add_const(short id, char** pool, char* value);
void pool_destroy(char** pool);

#endif