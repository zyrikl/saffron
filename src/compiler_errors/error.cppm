module;

#include <cstdlib>

export module error;

import std;

export namespace error {
    enum type {
        SYNTAX, LINKER
    };
    std::string error_log(type) {
        std::cerr << "Error" << std::endl;
        std::exit(1);
    } 
}