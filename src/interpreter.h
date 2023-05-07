#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <vector>

#include "stack.h"
#include "commands.h"

class Interpreter {
    public:
        Interpreter();
        void interpret(std::vector<instruction>* instrs);

    private:
        Stack stack;
        
        ssize_t instr_p;
        ssize_t end;
        std::vector<instruction>* instrs;

        void set_ip(ssize_t offs);
        void execute_instr();
};

#endif
