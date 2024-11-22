
#include "stringStack.h"
#include <stdlib.h>
#include <stdio.h>

struct stringStack {
    char ** stack;
    size_t size;
    size_t capacity;
} ;

stringStack * initStringStack(){
    stringStack * stack = (stringStack *)malloc(sizeof(stringStack));
    stack->stack = (char **)malloc(STACK_CHUNK_SIZE * sizeof(char *));
    stack->size = 0;
    stack->capacity = STACK_CHUNK_SIZE;
    return stack;
}

void growStack(stringStack * stack){
    printf("Growing stack\n");
    stack->capacity += STACK_CHUNK_SIZE;
    stack->stack = (char **)realloc(stack->stack, stack->capacity * sizeof(char *));
}

void reduceStack(stringStack * stack){
    printf("Reducing stack\n");
    stack->capacity -= STACK_CHUNK_SIZE;
    stack->stack = (char **)realloc(stack->stack, stack->capacity * sizeof(char *));
}

void pushStringStack(stringStack * stack, char *str){
    if(stack->size == stack->capacity){
        growStack(stack);
    }
    stack->stack[stack->size++] = str;
}

char * popStringStack(stringStack * stack){
    if(stack->size == 0){
        return NULL;
    }
    char * str = stack->stack[--stack->size];
    if((stack->size) % STACK_CHUNK_SIZE == 0){
        reduceStack(stack);
    }
    return str;
}

size_t stackSize(stringStack * stack){
    return stack->size;
}

boolean stackIsEmpty(stringStack * stack){
    return stack->size == 0;
}

char * peek(stringStack * stack){
    if(stack->size == 0){
        return NULL;
    }
    return stack->stack[stack->size - 1];
}

void freeStack(stringStack * stack){
    if(stack != NULL && stack->stack != NULL){
        free(stack->stack);
        free(stack);
    }
}
