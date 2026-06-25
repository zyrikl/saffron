#pragma once

#include <unordered_map>
#include <string>

namespace token {
    enum type {
        HASHTAG, 

        LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
        COMMA, PERIOD, PLUS, MINUS, STAR, SLASH,

        BANG, BANG_EQUAL,
        EQUAL, EQUAL_EQUAL,
        GREATER, GREATER_EQUAL,
        LESS, LESS_EQUAL,

        AMP, AMP_AMP,
        PIPE, PIPE_PIPE,

        EOF_TOKEN
    };

    std::unordered_map<type, std::string> type_debug_table = {
        { HASHTAG,             "hashtag (#)"        },
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
        { EOF_TOKEN,           "eof ()"             }
    };
}