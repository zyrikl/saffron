#include "scanner.h"
#include "error.h"
#include <cctype>

bool is_alpha(char c) {
    return (std::isalpha(c) || c == '_');
}
bool is_alpha_numeric(char c) {
    return (std::isalpha(c) || c == '_' || std::isdigit(c));
}

Scanner::Scanner(std::string source): source(source) {}

char Scanner::advance() {
    return source[current++];
}

void Scanner::add(token::type type, std::any literal) {
    std::string text = source.substr(start, current - start);
    tokens.push_back(Token(type, text, literal, line));
}
void Scanner::add(token::type type) {
    add(type, "null");
}

bool Scanner::match(char expected) {
    if (current >= source.length()) return false;
    if (source[current] != expected) return false;

    current++;
    return true;
}
char Scanner::peek() {
    if (current >= source.length()) return '\0';
    return source[current];
}
char Scanner::peek_next() {
    if (current + 1 >= source.length()) return '\0';
    return source[current + 1];
} 

void Scanner::string(char beginning) {
    while (peek() != beginning && current < source.length()) {
        if (peek() == '\n') {
            line++;
        }
        column++;
        advance();
    }

    if (current >= source.length()) {
        error::message("Unterminated string", line, column);
        return;
    }

    advance();
    column++;

    std::string value = source.substr(start + 1, current - start - 2);
    add(token::STRING, value);
}
void Scanner::number() {
    while (std::isdigit(peek())) advance();

    if (peek() == '.' && isdigit(peek_next())) {
        advance();
        while (isdigit(peek())) advance();
    }

    add(token::NUMBER, std::stod((source.substr(start, current - start))));
}
void Scanner::identifier() {
    while (is_alpha_numeric(peek())) advance();

    std::string text = source.substr(start, current - start);
    token::type t;
    if (identifier_table.contains(text)) {
        t = identifier_table[text];
    } else {
        t = token::IDENTIFIER;
    }
    add(t);
}

std::vector<Token> Scanner::scan_tokens() {
    while (current < source.length()) {
        start = current;
        column++;
        
        char c = advance();
        switch (c) {
            case '#':
                while (peek() != '\n' && current < source.length()) advance();
            case '(':
                add(token::LEFT_PAREN); break;
            case ')':
                add(token::RIGHT_PAREN); break;
            case '{':
                add(token::LEFT_BRACE); break;
            case '}':
                add(token::RIGHT_BRACE); break;
            case ',':
                add(token::COMMA); break;
            case '.':
                add(token::PERIOD); break;
            case '+':
                add(token::PLUS); break;
            case '-':
                add(token::MINUS); break;
            case '*':
                add(token::STAR); break;
            case '/':
                add(token::SLASH); break;
            case '!':
                add(match('=') ? token::BANG_EQUAL : token::BANG); break;
            case '=':
                add(match('=') ? token::EQUAL_EQUAL : token::EQUAL); break;
            case '>':
                add(match('=') ? token::GREATER_EQUAL : token::GREATER); break;
            case '<':
                add(match('=') ? token::LESS_EQUAL : token::LESS); break;
            case '&':
                add(match('&') ? token::AMP_AMP : token::AMP); break;
            case '|':
                add(match('=') ? token::PIPE_PIPE : token::PIPE); break;
            case '"':
                string('"'); break;
            case '\'':
                string('\''); break;
            case ' ':
            case '\r':
            case '\t':
                break;
            case '\n':
                add(token::NEWLINE);
                line++;
                column = 0;
                break;
            default:
                if (std::isdigit(c)) {
                    number();
                } else if (is_alpha(c)) {
                    identifier();
                } else {
                    error::message("Unexpected character", line, column);
                }
                break;
        }
    }

    tokens.push_back(Token(token::EOF_TOKEN, "", "eof", line));
    return tokens;
}