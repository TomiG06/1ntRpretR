#include <unistd.h>
#include <stdio.h>
#include "interpreter.h"

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
