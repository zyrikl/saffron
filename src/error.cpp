#include "error.h"
#include <cstdlib>
#include <iostream>

namespace error {
    void error_log(std::string message) {
        std::cerr << message << std::endl;
        std::exit(1);
    }
    void message(std::string message, int line, int column) {
        std::cerr << message + std::string(" on line ") + std::to_string(line) + std::string(", column ") + std::to_string(column) << std::endl;
        std::exit(1);
    }
    void warning_log(std::string message) {
        std::cerr << message << std::endl;
        std::exit(1);
    } 
}