#include "error.h"
#include <cstdlib>
#include <iostream>

namespace error {
    void error_log(std::string message) {
        std::cerr << message << std::endl;
        std::exit(1);
    }
    void warning_log(std::string message) {
        std::cerr << message << std::endl;
        std::exit(1);
    } 
}