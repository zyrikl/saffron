#include "ast.h"

Token::Token(std::string type, std::any value, int line, int column = 1) 
        : type(type), value(value), line(line), column(column) {}

std::string Token::location() {
    return "line {$this->line}, column {$this->column}";
}

std::string Token::toString() {
    return value !== NULL
        ? "{$this->type}({$this->value})@{$this->line}:{$this->column}"
        : "{$this->type}@{$this->line}:{$this->column}";
}