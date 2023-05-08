#include <vector>
#include <cstdint>

#include "helpers.h"
#include "interpreter.h"
#include "stack.h"

Interpreter::Interpreter() {
    this->stack = Stack();
}

void Interpreter::set_ip(ssize_t offs) {
    offs -= 1;
    if(0 > offs || offs > this->end-1) {
        error("Pointer out of bounds" + std::to_string(offs));
    }

    this->instr_p = offs-1;
}

void Interpreter::execute_instr() {
    /* Some variables that help thorugh execution */
    int64_t a, b;

    instruction instr = this->instrs->at(this->instr_p);

    switch(instr.opcode) {
        case PUSH:
            this->stack.push(instr.operand);
            break;
        case POP:
            this->stack.pop();
            break;
        case ADD:
        case MUL:
        case SWAP:
            a = this->stack.peek();
            this->stack.pop();
            b = this->stack.peek();
            this->stack.pop();

            switch(instr.opcode) {
                case ADD:
                    this->stack.push(a + b);
                    break;
                case MUL:
                    this->stack.push(a * b);
                    break;
                case SWAP:
                    this->stack.push(a);
                    this->stack.push(b);
                    break;
            }
            break;
        case IFEQ:

        #pragma GCC diagnostic ignored "-Wimplicit-fallthrough"
            if(this->stack.peek() == 0) break;
        #pragma GCC diagnostic pop

        case JUMP:
            Interpreter::set_ip(instr.operand);
            break;
        case PRINT:
            if(instr.operand == 1) {
                std::putchar(this->stack.peek());
            } else {
                std::printf("%ld", this->stack.peek());
            }
            break;
        case DUPL:
            this->stack.push(this->stack.peek());
            break;
        case EXIT:
            exit(0);
            break;
        case IGNORE:
            break;
    }
}

void Interpreter::interpret(std::vector<instruction>* instrs) {
    this->end = instrs->size();

    /* Not really a pointer, more like an index */
    this->instr_p = 0;
    this->instrs = instrs;

    while(this->instr_p < this->end) {
        Interpreter::execute_instr();
        ++this->instr_p;
    }
}
