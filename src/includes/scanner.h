#pragma once

#include <vector>
#include <string>
#include "token.h"

class Scanner {
    public:
        std::string source;
        std::vector<Token> tokens;

        std::unordered_map<std::string, token::type> identifier_table = {
            { "if",                  token::IF         },
            { "else",                token::ELSE       },
            { "do",                  token::DO         },
            { "while",               token::WHILE      },
            { "class",               token::CLASS      },
            { "from",                token::FROM       },
            { "func",                token::FUNC       },
            { "return",              token::RETURN     },
            { "let",                 token::LET        },
            // function names and constructs
            { "echo",                token::ECHO       },
        };

        Scanner(std::string source);
        std::vector<Token> scan_tokens();
    private:
        int start = 0;
        int current = 0;
        int line = 1;
        int column = 0;

        char advance();
        void add(token::type type);
        void add(token::type type, std::any literal);

        bool match(char expected);
        char peek();
        char peek_next();

        void string(char beginning);
        void number();
        void identifier();
};