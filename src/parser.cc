#include <iostream>
#include <string>
#include <vector>
#include <cctype>

#include "commands.h"
#include "parser.h"
#include "helpers.h"

std::vector<std::string> Parser::split(std::string txt) {
    
    /* Start and end indices */
    size_t start = 0;
    size_t end = start;

    /* Null terminate the string to make our lives easier (I guess..) */
    txt.push_back('\0');
    size_t limit = txt.length();

    std::vector<std::string> ret = {};

    while(end < limit) {

        if(txt[end] == ' ' || txt[end] == '\t' || txt[end] == '\0') {
            ret.push_back(std::string(&txt[start], &txt[end]+1));

            if(txt[end] == '\0') break;
            
            while(txt[end] == ' ' || txt[end] == '\t') ++end;

            start = end;
        }

        ++end;
    }
    
    return ret;
}

/* 
    This was used in the first implementation which used
    the C programming language

    There prabably are better ways to trim a string in C++..
*/
std::string Parser::trim(std::string txt, char del) {
    size_t len = txt.length();

    if(len == 0) return "";

    /* removes char to trim in the end while there is one */

    while(txt[len-1] == del) --len;

    if(len == 0) return "";

    /*
        Removes char to trim in the beginning provided that there is one.
        Due to the fact that a char is removed, length must decrement.
    */

    /* This line is probably not really safe */
    char* str = (char*) txt.c_str(); 

    while(str[0] == del) ++str, --len;
    return std::string(str, str + len);
}

int64_t Parser::to_number(std::string txt) {
    for(char &c: txt) {
        if(!isdigit(c) && c != '-' && c != '+') error(txt << "is not a decimal number");
    }

    return std::atoll(txt);
}

