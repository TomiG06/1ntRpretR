#include <cstdlib>
#include "stack.h"
#include "helpers.h"

void Stack::push(int64_t num) {
    if(this->TOP == MAX) {
        error("Stack Overflow");
    }
    this->stack.push_back(num);
    ++this->TOP;
}

void Stack::pop() {
    if(this->TOP == 0) {
        error("Empty Stack");
    }
    
    this->stack.pop_back();
    --this->TOP;
}

int64_t Stack::peek() {
    return this->stack[this->TOP-1];
}

Stack::Stack() {
    this->stack = {};
    this->TOP = 0;
}

