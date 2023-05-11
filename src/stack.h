#ifndef STACK_H
#define STACK_H

/*
    Stack implementation used at runtime
*/

#include <vector>
#include <cstdint>

#define MAX 0xFF

class Stack {
    private:
        std::vector<int64_t> stack;
        int16_t TOP;

    public:
        Stack();
        void push(int64_t num);
        void pop();
        int64_t peek();
};

#endif

