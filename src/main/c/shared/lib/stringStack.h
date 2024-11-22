

#ifndef STRING_STACK_H
#define STRING_STACK_H

#include <stddef.h>
#include "Type.h"

#define STACK_CHUNK_SIZE 15

typedef struct stringStack stringStack;

stringStack * initStringStack();

void pushStringStack(stringStack * stack, char *str);

char * popStringStack(stringStack * stack);

size_t stackSize(stringStack * stack);

boolean stackIsEmpty(stringStack * stack);

char * peek(stringStack * stack);

void freeStack(stringStack * stack);

#endif