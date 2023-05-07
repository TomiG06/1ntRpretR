#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

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
            ret.push_back(std::string(&txt[start], &txt[end]));

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

int64_t Parser::to_integer(std::string txt) {
    for(char &c: txt) {
        if(!isdigit(c) && c != '-' && c != '+') {
            error(txt + "is not a decimal number");
        }
    }

    return std::strtoll(txt.c_str(), NULL, 10);
}

instruction Parser::parse_line(std::string txt, ssize_t line_N) {
    txt = Parser::trim(txt, '\n');
    txt = Parser::trim(txt, ' ');

    std::vector<std::string> seped = Parser::split(txt);

    instruction ret;

    ret.operand = 0;

    if(seped[0] == "" || seped[0][0] == '#') {
        ret.opcode = IGNORE;
        return ret;
    }

    bool found = false;
    std::transform(seped[0].cbegin(), seped[0].cend(), seped[0].begin(), tolower);

    for(uint8_t i = 0; i < CMD_N; ++i) {
        if(commands[i].cmd == seped[0]) {
            ret.opcode = commands[i].opcode;

            if(commands[i].operand_N != seped.size()-1) {
                error("Line " + std::to_string(line_N) + ": Command '" + seped[0] + "' expects " 
                        + std::to_string(commands[i].operand_N) + " operands but was given " + std::to_string(seped.size()-1));
            }

            if(commands[i].operand_N > 0) {
                ret.operand = Parser::to_integer(seped[1]);
            }

            found = true;

            break;
        }
    }

    if(!found) {
        error("Line " + std::to_string(line_N) + ": Uknown command '" + seped[0] + "'");
    }

    return ret;
}

std::vector<instruction> Parser::parse(std::string fname) {
    std::ifstream f(fname);

    std::string line;
    std::vector<instruction> instructions;
    instruction instr;
    ssize_t lineN = 1;
    

    while(std::getline(f, line)) {
        instr = Parser::parse_line(line, lineN);

        instructions.push_back(instr);

        ++lineN;
    }

    f.close();

    return instructions;
}

