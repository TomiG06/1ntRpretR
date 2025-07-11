# 1ntRpretR

based on an [answer](https://stackoverflow.com/questions/6887471/how-would-i-go-about-writing-an-interpreter-in-c) on Stack Overflow

## Briefly

This is an interpreter implementation for a stack based assembly-like language. It used to be written in C but because the whole program was shit I reimplemented it in C++.

## Environment
* 10 commands (see below for more details)
* a stack with 2^8 positions ready to be used

## Commands
* PUSH:     Push a number in the stack
* POP:      Pop from the stack
* ADD:      Add first 2 numbers of the stack and store the result on the top
* MUL:      Multiply ...
* JUMP:     Jump to given line 
* IFEQ:     JUMP if the top of the stack evaluates to true
* PRINT:    Print top of the stack either ascii or numeric
* DUPL:     PUSH copy of the top of the stack
* SWAP:     Swap first 2 numbers of the stack
* EXIT:     Program exit

## Update July 12 2025

I have no idea what the fuck i was thinking when i implemented the `JUMP` command back then. Like why would line count even matter? I will probably make it jump to the number of the instruction in the sequence some day.


