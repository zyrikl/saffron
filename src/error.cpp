#include "error.h"
#include <cstdlib>
#include <iostream>
#include <stdexcept>

namespace error {
    void error_log(std::string message) {
        throw std::runtime_error(std::string("\x1b[31mError: \x1b[0m") + message);
    }
    void message(std::string message, int line, int column) {
        throw std::runtime_error(std::string("\x1b[31mError: \x1b[0m") + message + std::string(" on line ") + std::to_string(line) + std::string(", column ") + std::to_string(column));
    }
    void warning_log(std::string message) {
        std::cerr << std::string("\x1b[35mWarning! \x1b[0m") + message << std::endl;
    } 
}