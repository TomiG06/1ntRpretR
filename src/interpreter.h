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
        
        /*
            instr_p: stores the location of next instruction
            start_p: stores the location of the beginning of instructions
            end_p:   stores the location of the end of instructions

            start_p and end_p define the bounds of where the instr_p can point
            from a mathematical perspective, the following statement must always be true:
            
            start_p <= instr_p <= end_p
        */
        ssize_t instr_p;
        ssize_t end;
        std::vector<instruction>* instrs;

        void set_ip(ssize_t offs);
        void execute_instr();
};

#endif
