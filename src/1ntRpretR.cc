#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>

#include "helpers.h"
#include "commands.h"
#include "parser.h"
#include "interpreter.h"


int main(int argc, char** argv) {
    if(argc != 2) {
        error("Wrong format\n\tUsage: 1ntRpretR <file>");
    }

    std::string fname(argv[1]);

    if(!std::filesystem::exists(fname)) {
        error("File '" + fname + "' does not exist");
    }

    Parser parsR = Parser();
    Interpreter _1ntRpretR = Interpreter();

    std::vector<instruction> instructions = parsR.parse(fname);

    _1ntRpretR.interpret(&instructions);

    return 0;
}

