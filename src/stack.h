#ifndef STACK_H
#define STACK_H

#include <stdint.h>

#define MAX 0xFF

class Stack {
    private:
        int64_t stack[MAX];
        int16_t TOP;

    public:
        Stack();
        void push(int64_t num);
        void pop();
        int64_t peek();
};

#endif

