#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "commands.h"

void interpret(FILE* source) {
    stack* s = stackInit(); //the stacl
    char buffer[256]; //Keeps command to be executed
    int bufferIndex = 0; //Keeps next free cell of buffer var
    char c;

    while((c = fgetc(source)) != EOF) {
        if(c == 10) { //Commands are seperated by LF
            buffer[bufferIndex] = 0; //NULL termination
            execute(s, source, buffer); //Execution
            memset(buffer, 256, 0); //Empty buffer
            bufferIndex = 0; //Uninitialize index
            continue;
        }
        buffer[bufferIndex++] = c;
    }

    free(s);

}
