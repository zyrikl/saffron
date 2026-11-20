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

#include <unordered_map>
#include <string>
#include <any>

namespace token {
    enum type {
        NEWLINE, 

        LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
        COMMA, PERIOD, PLUS, MINUS, STAR, SLASH,

        BANG, BANG_EQUAL,
        EQUAL, EQUAL_EQUAL,
        GREATER, GREATER_EQUAL,
        LESS, LESS_EQUAL,

        AMP, AMP_AMP,
        PIPE, PIPE_PIPE,

        IDENTIFIER, STRING, NUMBER,

        IF, ELSE, 
        DO, WHILE,
        CLASS, FROM,
        FUNC, RETURN,
        LET,

        // function names and constructs
        ECHO,

        EOF_TOKEN
    };

    inline std::unordered_map<type, std::string> type_debug_table = {
        { NEWLINE,             "newline (n)"        },
        { LEFT_PAREN,          "left_paren (()"     },
        { RIGHT_PAREN,         "right_paren ())"    },
        { LEFT_BRACE,          "left_brace ({)"     },
        { RIGHT_BRACE,         "right_brace (})"    },
        { COMMA,               "comma (,)"          },
        { PERIOD,              "period (.)"         },
        { PLUS,                "plus (+)"           },
        { MINUS,               "minus (-)"          },
        { STAR,                "star (*)"           },
        { SLASH,               "slash (/)"          },
        { BANG,                "bang (!)"           },
        { BANG_EQUAL,          "bang_equal (!=)"    },
        { EQUAL,               "equal (=)"          },
        { EQUAL_EQUAL,         "equal_equal (==)"   },
        { GREATER,             "greater (>)"        },
        { GREATER_EQUAL,       "greater_equal (>=)" },
        { LESS,                "less (<)"           },
        { LESS_EQUAL,          "less_equal (<=)"    },
        { AMP,                 "amp (&)"            },
        { AMP_AMP,             "amp_amp (&&)"       },
        { PIPE,                "pipe (|)"           },
        { PIPE_PIPE,           "pipe_pipe (||)"     },
        { IDENTIFIER,          "identifier"         },
        { STRING,              "string"             },
        { NUMBER,              "number"             },
        { IF,                  "if"                 },
        { ELSE,                "else"               },
        { DO,                  "do"                 },
        { WHILE,               "while"              },
        { CLASS,               "class"              },
        { FROM,                "from"               },
        { FUNC,                "func"               },
        { RETURN,              "return"             },
        { LET,                 "let"                },
        // function names and constructs
        { ECHO,                "echo"               },

        { EOF_TOKEN,           "eof ()"             }
    };
}

class Token {
    public:
        token::type type;
        std::string lexeme;
        std::any literal;
        int line;

        Token(token::type type, std::string lexeme, std::any literal, int line);

        std::string to_string();
        std::string any_to_string(const std::any& a);
};