#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include "stack.h"

enum {
    PUSH = 0,
    POP,
    ADD,
    SUB,
    IFEQ,
    JUMP,
    PRINT,
    DUPL,
    MUL,
    IGNORE,
    SWAP
};

char commands_with_param[] = {PUSH, IFEQ, JUMP, PRINT};
size_t cwp_length = sizeof(commands_with_param);

char command_uses_param(char command) {
    for(size_t i = 0; i < cwp_length; ++i) {
        if(commands_with_param[i] == command) return 1;
    }
    return 0;
}

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

//Does sub, add and mul
int64_t ArithmeticOp(stack *s, size_t op) {
    int64_t first = peek_stack(s);
    pop_from_stack(s);
    int64_t second = peek_stack(s);
    pop_from_stack(s);
    
    switch(op) {
        case ADD:
            push_in_stack(s, second+first);
            break;
        case SUB:
            push_in_stack(s, second-first);
            break;
        case MUL:
            push_in_stack(s, second*first);
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

//https://stackoverflow.com/questions/122616/how-do-i-trim-leading-trailing-whitespace-in-a-standard-way
char* trim(char* str, char del) {
    size_t len = strlen(str);
    while(str[len-1] == del) --len; //removes char to trim in the end while there is one
    /*
        removes char to trim in the beginning while there is one
        due to the fact that a char is removed, length must decrement
    */
    while(str[0] == del) ++str, --len;
    return strndup(str, len);
}

//Returns array with command and operand if exists
int64_t* parse_line(char* uncleaned_statement) {
    char* statement = trim(uncleaned_statement, ' ');
    
    int64_t* ret = (int64_t*)malloc(2*sizeof(int64_t));
    //Check if line should be ignored
    if(statement[0] == '#' || !strcmp(statement, "")) {
        ret[0] = IGNORE;
        return ret;
    }

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

    if(!strcmp(command, "push")) ret[0] = PUSH;
    else if(!strcmp(command, "pop")) ret[0] = POP;
    else if(!strcmp(command, "add")) ret[0] = ADD;
    else if(!strcmp(command, "sub")) ret[0] = SUB;
    else if(!strcmp(command, "ifeq")) ret[0] = IFEQ;
    else if(!strcmp(command, "jump")) ret[0] = JUMP;
    else if(!strcmp(command, "print")) ret[0] = PRINT;
    else if(!strcmp(command, "dupl")) ret[0] = DUPL;
    else if(!strcmp(command, "mul")) ret[0] = MUL;
    else if(!strcmp(command, "swap")) ret[0] = SWAP;
    else {
        fprintf(stderr, "'%s' command not found\n", command);
        free(command);
        free(operand);
        exit(1);
    }

    if(command_uses_param(ret[0])) {
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
void execute(stack* s, FILE* f, int64_t* parts);

#endif
