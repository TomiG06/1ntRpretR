#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "stack.h"
#include "commands.h"

#define EXTRACT_OP(NUM)     (NUM >> 32)
#define EXTRACT_IMM(NUM)    ((NUM << 32) >> 32)
#define MAX_MEM             (1 << 12)

/*
    'Hardware' components

    Stack is declared in the main function
*/
int64_t memory[MAX_MEM];    //Memory
int32_t PC = 0;             //Program Counter

void execute(stack* s, FILE* f, int64_t* instr) {
    uint8_t op = EXTRACT_OP(*(instr));
    int32_t imm = EXTRACT_IMM(*(instr));
    
    switch(op) {
        case PUSH:
            push_in_stack(s, imm);
            break;
        case POP:
            pop_from_stack(s);
            break;
        case ADD:
        case SUB:
        case MUL:
            ArithmeticOp(s, op);
            break;
        case IFEQ:
            if(!peek_stack(s)) break;
        case JUMP:
            PC = imm - 1;
            break;
        case PRINT:
        /*
            true:  print ascii value
            false: print numeric value
        */
            if(imm) putchar(peek_stack(s));
            else printf("%ld", peek_stack(s));
            break;
        case DUPL:
            push_in_stack(s, peek_stack(s));
            break;
        case SWAP:
            {
                int32_t swap1, swap2;
                if(s->TOP > 0) {
                    swap1 = peek_stack(s);
                    pop_from_stack(s);
                    swap2 = peek_stack(s);
                    pop_from_stack(s);
                    push_in_stack(s, swap1);
                    push_in_stack(s, swap2);
                }
            }
        case IGNORE:
            break;
    }
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
    
    //Buffer to keep each instruction
    int64_t bytecode_buffer;

    //The stack
    stack* s = stackInit();
    
    size_t x = 0;
    while(fread(&bytecode_buffer, sizeof(bytecode_buffer), 1, sc)) memory[x++] = bytecode_buffer;
    fclose(sc);

    //Startign execution
    while(memory[PC]) execute(s, NULL, &memory[PC++]);

    free(s);
}
