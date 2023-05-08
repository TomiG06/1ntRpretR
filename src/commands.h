#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>
#include <iostream>
#include <cstdint>

enum {
    PUSH = 0,   //00
    POP,        //01
    ADD,        //02
    IFEQ,       //03
    JUMP,       //04
    PRINT,      //05
    DUPL,       //06
    MUL,        //07
    SWAP,       //08
    EXIT,       //09

    CMD_N,
    IGNORE      //10
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
