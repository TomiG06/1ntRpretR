//Basic stack implementation

#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define MAX 0xff

typedef struct {
    int64_t _stack[MAX];
    size_t TOP;
} stack;

uint8_t stack_is_full(stack *s) {
    if(s->TOP == MAX-1) return 1;
    return 0;
}

uint8_t stack_is_empty(stack *s) {
    if(s->TOP == -1) return 1;
    return 0;
}

void push_in_stack(stack *s, int64_t num) {
    if(stack_is_full(s)) {
        free(s);
        fprintf(stderr, "Error: Stack Overflow\n");
        exit(1);
    }
    s->_stack[++s->TOP] = num;
}

void pop_from_stack(stack *s) {
    if(stack_is_empty(s)) {
        free(s);
        fprintf(stderr, "Error: Empty Stack\n");
        exit(1);
    }
    
    s->_stack[s->TOP--] = 0;
}

int64_t peek_stack(stack *s) {
    return s->_stack[s->TOP];
}

stack *stackInit() {
    stack* temp = (stack*) malloc(sizeof(stack));
    temp->TOP = -1;
    return temp;
}

#endif
