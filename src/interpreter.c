#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "stack.h"
#include "commands.h"

void execute(stack* s, FILE* f, int64_t* parts) {
    switch(parts[0]) {
        case PUSH:
            push_in_stack(s, parts[1]);
            break;
        case POP:
            pop_from_stack(s);
            break;
        case ADD:
        case SUB:
        case MUL:
            ArithmeticOp(s, parts[0]);
            break;
        case IFEQ:
            if(peek_stack(s)) perfJMP(parts[1]-1, f);
            break;
        case JUMP:
            perfJMP(parts[1]-1, f);
            break;
        case PRINT:
        /*
            1: print ascii value
            0: print numeric value
        */
            if(parts[1] == 1) putchar(peek_stack(s));
            else if(!parts[1]) printf("%ld", peek_stack(s));
            else {
                fprintf(stderr, "Error: invalid parameter '%ld'\n", parts[1]);
                free(parts);
                free(s);
                exit(1);
            }
            break;
        case DUPL:
            push_in_stack(s, peek_stack(s));
            break;
        case SWAP:
            if(s->TOP > 0) {
                int64_t swap1 = peek_stack(s);
                pop_from_stack(s);
                int64_t swap2 = peek_stack(s);
                pop_from_stack(s);
                push_in_stack(s, swap1);
                push_in_stack(s, swap2);
            }
            break;
        case IGNORE:
            break;
    }

    free(parts);
}

void interpret(FILE* source) {
    stack* s = stackInit(); //the stack
    char buffer[256]; //Keeps command to be executed
    size_t len;

    while(fgets(buffer, 256, source) != NULL) {
        len = strlen(buffer);
        if(buffer[len-1] == 10) buffer[len-1] = 0;
        execute(s, source, parse_line(buffer));
    }

    free(s);
}

int main(int argc, char* argv[]) {

    //Check for source code
    if(argc == 1) {
        fprintf(stderr, "No input file\n");
        return 1;
    }

    //Check if file exists
    if(access(argv[1], F_OK)) {
        fprintf(stderr, "File %s does not exist\n", argv[1]);
        return 1;
    }
    FILE *sc = fopen(argv[1], "r");

    //Check for errors
    if(sc == NULL) {
        fprintf(stderr, "Error occured while opening file\n");
        return 1;
    }

    //Start interpretation
    interpret(sc);

    fclose(sc);
    return 0;
}

