#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "commands.h"

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
