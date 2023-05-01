#include <iostream>
#include <helpers.h>

void err(std::string msg) {
    std::cout << "Error: " << msg << std::endl;
    exit(1);
}
