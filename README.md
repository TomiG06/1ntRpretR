# 1ntRpretR

based on an [answer](https://stackoverflow.com/questions/6887471/how-would-i-go-about-writing-an-interpreter-in-c) on Stack Overflow

## Briefly

Used to contain only an interpreter, now it also contains a bytecode compiler and a vm to run the bytecode. I kept the same name because I was just bored to change it. Anyway this thing is just built for fun :)

## Environment
* 9 commands (see below for more details)
* a stack with 2^8 positions ready to be used

## Commands
* PUSH: Push a number in the stack
* POP: Pop from the stack
* ADD: Add first 2 numbers of the stack and store it in top
* SUB: Subtract ..
* MUL: Multiply ...
* JUMP: Jump to given line
* IFEQ: JUMP if the top of the stack evaluates to true
* PRINT: Print top of the stack either ascii or numeric
* DUPL: PUSH copy of the top of the stap
* SWAP: Swap first 2 numbers of the stack