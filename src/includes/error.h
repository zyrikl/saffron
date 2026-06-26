#pragma once

#include <string>

namespace error {
    void error_log(std::string message);
    void message(std::string message, int line, int column = 1);
    void warning_log(std::string message);
}