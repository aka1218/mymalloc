#ifndef MYMALLOC_H
#define MYMALLOC_H
#define MEM_SIZE 4096

#include <stdlib.h>
#include <stdio.h>


void *mymalloc(size_t size, char *file, int line);

void myfree(void *ptr, char *file, int line);

#define malloc(s) mymalloc(s, __FILE__, __LINE__);

#define free(p) myfree(p, __FILE__, __LINE__);
