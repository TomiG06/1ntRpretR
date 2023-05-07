#include <cstdlib>
#include "stack.h"
#include "helpers.h"

void Stack::push(int64_t num) {
    if(this->TOP == 0xff) {
        error("Stack Overflow");
    }
    this->stack.push_back(num);
    this->TOP += 1;
}

void Stack::pop() {
    if(this->TOP == -1) {
        error("Empty Stack");
    }
    
    this->stack.pop_back();
    this->TOP -= 1;
}

int64_t Stack::peek() {
    if(this->TOP == -1) {
        error("Empty Stack");
    }
    return this->stack[this->TOP];
}

Stack::Stack() {
    this->stack = {};
    this->TOP = -1;
}

