#ifndef POOL_H_
#define POOL_H_

//Functions to create/destoy pool of constants and to add/get constants to/from pool.
char** pool_create();
char* get_const(short id, char** pool);
void add_const(short id, char** pool, char* value);
void pool_destroy(char** pool);

#endif