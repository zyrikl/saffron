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

#include "token.h"

std::string Token::any_to_string(const std::any& a) {
    if (!a.has_value()) {
        return "";
    }
    
    if (a.type() == typeid(std::string)) {
        return std::any_cast<std::string>(a);
    }
    if (a.type() == typeid(const char*)) {
        return std::any_cast<const char*>(a);
    }
    if (a.type() == typeid(int)) {
        return std::to_string(std::any_cast<int>(a));
    }
    if (a.type() == typeid(double)) {
        return std::to_string(std::any_cast<double>(a));
    }

    return "Unsupported Type";
}

Token::Token(token::type type, std::string lexeme, std::any literal, int line): type(type), lexeme(lexeme), literal(literal), line(line) {}

std::string Token::to_string() {
    return std::string("Token: ")+token::type_debug_table[type]+std::string(", lexeme: ")+lexeme+std::string(", literal: ")+any_to_string(literal)+std::string(", on line ")+std::to_string(line);
}