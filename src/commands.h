#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>
#include <iostream>
#include <cstdint>

enum {
    PUSH = 0,   //00
    POP,        //01
    ADD,        //02
    SUB,        //03
    IFEQ,       //04
    JUMP,       //05
    PRINT,      //06
    DUPL,       //07
    MUL,        //08
    SWAP,       //09
    EXIT,       //10

    CMD_N,
    IGNORE      //12
};

typedef struct {
    uint8_t     opcode;
    std::string cmd;
    uint8_t     operand_N;
} command;

const command commands[CMD_N] = {
    {PUSH,  "push",     1},
    {POP,   "pop" ,     0},
    {ADD,   "add",      0},
    {SUB,   "sub",      0},
    {IFEQ,  "ifeq",     1},
    {JUMP,  "jump",     1},
    {PRINT, "print",    1},
    {DUPL,  "dupl",     0},
    {MUL,   "mul",      0},
    {SWAP,  "swap",     0},
    {EXIT,  "exit",     0}
};

typedef struct {
    uint8_t opcode;
    int64_t operand;
} instruction;

#endif
