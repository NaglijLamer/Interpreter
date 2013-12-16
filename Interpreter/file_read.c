//File with functions that can read file with byte-code. And create a massive from byte-code functions.

#include <stdio.h>
#include "file_read.h"
#include "instant_exit.h"

//Reading of the fileheader.
file_header* read_file_head(FILE** file)
{
	file_header* fh;
	fread(fh, sizeof(fh), sizeof(fh), *file);
}