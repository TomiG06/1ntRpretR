#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include "stack.h"

//In order not to use 'magic numbers'
enum {
    push = 0,
    pop,
    add,
    sub,
    ifeq,
    jump,
    print,
    dupl,
    blank_line
};

//Checks if operand is decimal number
uint8_t OperandIsNumber(char* str) {
    for(int x = 0; x < strlen(str); x++) {
        if(!isdigit(str[x])) {
            fprintf(stderr, "'%s' operand is not a decimal number\n", str);
            exit(1);
        }
    }
    return 10;
}

//Does sub and add
int64_t ArithmeticOp(stack *s, size_t op) {
    int64_t first = peek_stack(s);
    pop_from_stack(s);
    int64_t second = peek_stack(s);
    pop_from_stack(s);
    
    switch(op) {
        case add:
            push_in_stack(s, second+first);
            break;
        case sub:
            push_in_stack(s, second-first);
            break;
        default:
            break;
    }
}

//Jump function
void perfJMP(int newLine, FILE* f) {
    if(newLine < 0) {
        fprintf(stderr, "Line must be positive number\n");
        exit(1);
    }
    int linec = 0;
    int pos = 0;
    char c;
    //Check from the begining of the file
    fseek(f, pos, SEEK_SET);
    while((c = fgetc(f)) != EOF) {
        if(c == 10) linec++; //10 is LF
        if(newLine == linec) {
            fseek(f, !newLine ? pos : pos+1, SEEK_SET);
            return;
        }
        pos++;
    }

    //Parsed whole file so line number is invalid
    fprintf(stderr, "Line limit surpassed\nLine given: %d | Limit: %d\n", newLine+1, linec+1);
    exit(1);
}

//Returns array with command and operand if exists
int64_t* parseLine(char* statement) {
    int64_t* ret = (int64_t*)malloc(2*sizeof(int64_t));
    size_t len = strlen(statement);
    char* command = (char*)calloc(len, 1); //Calloc to not have to null terminate
    char space_is_met = 0;
    char* operand = (char*)calloc(len, 1); //Same
    size_t index = 0;

    for(size_t l = 0; l < len; ++l) {
        if(statement[l] == ' ') {
            if(statement[l+1] == ' ') continue;
            if(!strlen(command)) continue;
            space_is_met = 1;
            continue;
        }
        if(!space_is_met) command[l] = statement[l];
        else operand[index++] = statement[l];
    }

    if(!strcmp(command, "push")) ret[0] = push;
    else if(!strcmp(command, "pop")) ret[0] = pop;
    else if(!strcmp(command, "add")) ret[0] = add;
    else if(!strcmp(command, "sub")) ret[0] = sub;
    else if(!strcmp(command, "ifeq")) ret[0] = ifeq;
    else if(!strcmp(command, "jump")) ret[0] = jump;
    else if(!strcmp(command, "print")) ret[0] = print;
    else if(!strcmp(command, "dupl")) ret[0] = dupl;
    else if(!strcmp(command, "")) ret[0] = blank_line;
    else {
        fprintf(stderr, "'%s' command not found\n", command);
        free(command);
        free(operand);
        exit(1);
    }

    if(ret[0] == push || ret[0] == ifeq || ret[0] == jump) {
        if(!strcmp(operand, "")) {
            fprintf(stderr, "Error: '%s' command must contain an operand\n", command);
            free(command);
            free(operand);
            exit(1);
        }
        ret[1] = strtol(operand, NULL, OperandIsNumber(operand));
    } else {
        if(strcmp(operand, "")) {
            fprintf(stderr, "Error: '%s' command uses no operand\n", command);
            free(command);
            free(operand);
            exit(1);
        }
    }

    free(command);
    free(operand);

    return ret;
}

//Checks for command and executes it 
char execute(stack* s, FILE* f, char* statement) {
    int64_t* parts = parseLine(statement);
    int64_t temp;

    switch(parts[0]) {
        case push:
            push_in_stack(s, parts[1]);
            break;
        case pop:
            pop_from_stack(s);
            break;
        case add:
        case sub:
            ArithmeticOp(s, parts[0]);
            break;
        case ifeq:
            if(peek_stack(s)) perfJMP(parts[1]-1, f);
            break;
        case jump:
            perfJMP(parts[1]-1, f);
            break;
        case print:
            putchar(peek_stack(s));
            break;
        case dupl:
            temp = peek_stack(s);
            push_in_stack(s, temp);
            break;
        case blank_line:
            break;
    }
}

#endif
