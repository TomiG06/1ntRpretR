#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "commands.h"

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


void interpret(FILE* source) {
    stack* s = stackInit(); //the stack
    char buffer[256]; //Keeps command to be executed
    size_t len;

    while(fgets(buffer, 256, source) != NULL) {
        len = strlen(buffer);
        if(buffer[len-1] == 10) buffer[len-1] = 0;
        execute(s, source, trim(buffer, ' '));
    }

    free(s);

}
