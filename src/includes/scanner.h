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