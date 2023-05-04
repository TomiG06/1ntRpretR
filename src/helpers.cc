#include <iostream>
#include "helpers.h"

void error(std::string msg) {
    std::cout << "Error: " << msg << std::endl;
    exit(1);
}
