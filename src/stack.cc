#include <cstdlib>
#include "stack.h"

void err(string msg) {
    cout << "Error: " << msg << endl;
    exit(1);
}

void Stack::push(int64_t num) {
    if(this->TOP == MAX) {
        err("Stack Overflow");
    }
    this->stack[this->TOP++] = num;
}

void Stack::pop() {
    if(this->TOP == 0) {
        err("Empty Stack");
    }
    
    this->stack[this->TOP--] = 0;
}

int64_t Stack::peek() { return this->_stack[this->TOP]; }

Stack::Stack() {
    this->TOP = 0;
    this->stack = {0};
}

