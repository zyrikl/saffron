#include "token.h"

std::string any_to_string(const std::any& a) {
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