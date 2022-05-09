/*
    Bytecode compiler implementation for the language

    It exports a file that contains the bytecode which
    can be ran through the Virtual Machine
    (The VM source code is contained in vm.c file)
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "commands.h"

#define MAX_LENGTH 0xff
#define MAX_IMM (1UL << 31) -1
#define MIN_IMM (1 << 31)

void compile_to_bytecode(FILE* sc, char* bc_filename) {
    char buffer[MAX_LENGTH];

    /*
        parse_line checks provides syntax error checking
        so we pass every line to check for syntax errors
    */
    while(fgets(buffer, MAX_LENGTH, sc)) free(parse_line(buffer));

    int64_t* parts = (int64_t*)malloc(2*sizeof(int64_t));
    uint64_t* bytecode = (uint64_t*) malloc(sizeof(uint64_t));
    size_t line = 1;
    FILE *bc = fopen(bc_filename, "wb");

    fseek(sc, 0, SEEK_SET);
    while(fgets(buffer, MAX_LENGTH, sc)) {
        parts = parse_line(buffer);

        if(parts[0] == IGNORE) continue;

        /*
            About these cases here it's better to use the interpreter
            check interpreter.c
        */
        if(parts[1] > MAX_IMM) {
            fprintf(stderr, "Error in line %ld:\n\tMax number you can use is %ld, you used %ld\n", line, MAX_IMM, parts[1]);
            exit(1);
        } else if(parts[1] < MIN_IMM) {
            fprintf(stderr, "Error in line %ld:\n\tMin number you can use is %d, you used %ld\n", line, MIN_IMM, parts[1]);
            exit(1);
        }
        
        bytecode[0] = (parts[0] << 32) | parts[1];
        fwrite(bytecode, sizeof(bytecode), 1, bc);
        line++;
    }

    free(parts);
    free(bytecode);
    fclose(bc);
}

int main(int argc, char* argv[]) {

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
    
    char bc_filename[100];
    if(argc == 3) strcpy(bc_filename, argv[2]);
    else {
        strcpy(bc_filename, argv[1]);
        strcat(bc_filename, ".bc");
    }

    //Compilation function
    compile_to_bytecode(sc, bc_filename);

    fclose(sc);
}
