# 1ntRpretR

based on an [answer](https://stackoverflow.com/questions/6887471/how-would-i-go-about-writing-an-interpreter-in-c) on Stack Overflow

## Briefly

This is an interpreter implementation for a stack based assembly-like language. It used to be written in C but because the whole program was a shit I reimplemented it in C++.

## Environment
* 11 commands (see below for more details)
* a stack with 2^8 positions ready to be used

## Commands
* PUSH:     Push a number in the stack
* POP:      Pop from the stack
* ADD:      Add first 2 numbers of the stack and store it in top
* SUB:      Subtract ..
* MUL:      Multiply ...
* JUMP:     Jump to given line
* IFEQ:     JUMP if the top of the stack evaluates to true
* PRINT:    Print top of the stack either ascii or numeric
* DUPL:     PUSH copy of the top of the stap
* SWAP:     Swap first 2 numbers of the stack
* EXIT:     Program exit
