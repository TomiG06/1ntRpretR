#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>
#include <iostream>
#include <cstdint>

enum {
    PUSH,
    POP,
    ADD,
    SUB,
    IFEQ,
    JUMP,
    PRINT,
    DUPL,
    MUL,
    SWAP,
    EXIT,

    CMD_N,
    IGNORE
};

typedef struct {
    uint8_t     opcode;
    std::string cmd;
    bool        has_operand;
} command;

const command commands[CMD_N] = {
    {PUSH,  "push",     true    },
    {POP,   "pop" ,     false   },
    {ADD,   "add",      false   },
    {SUB,   "sub",      false   },
    {IFEQ,  "ifeq",     true    },
    {JUMP,  "jump",     true    },
    {PRINT, "print",    true    },
    {DUPL,  "dupl",     false   },
    {MUL,   "mul",      false   },
    {SWAP,  "swap",     false   },
    {EXIT,  "exit",     false   }
};

typedef struct {
    uint8_t opcode;
    int64_t operand;
} instruction;

#endif
