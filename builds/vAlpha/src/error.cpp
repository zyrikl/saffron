/*
    Copyright (C) 2026  Charles Wang

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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