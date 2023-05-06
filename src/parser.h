#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include "commands.h"

class Parser {
    public:
        std::vector<instruction>    parse(std::string fname);

        instruction     parse_line(std::string txt, ssize_t line_N);

    private:
        std::string trim(std::string txt, char del);

        std::vector<std::string> split(std::string txt);

        int64_t to_integer(std::string txt);

};

#endif

