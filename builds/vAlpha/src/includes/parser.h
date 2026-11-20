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

#include "token.h"
#include "ast.h"
#include <vector>
#include <string>
#include <memory>
#include <map>

class Parser {
    std::vector<Token> tokens;
    size_t current_token_number = 0;
    Token current_token = tokens[current_token_number];

    std::map<token::type, int> binop_precedence {
        { token::PLUS,      20 },
        { token::MINUS,     20 },
        { token::STAR,      40 },
        { token::SLASH,     40 }
    };

    public:
        Parser(std::vector<Token> tokens);

        Token get_next_token();
        int get_token_precedence();

        std::unique_ptr<ExprAST> parse_expression();
        std::unique_ptr<ExprAST> parse_primary();

        std::unique_ptr<ExprAST> parse_number_expr();
        std::unique_ptr<ExprAST> parse_paren_expr();
        std::unique_ptr<ExprAST> parse_identifier_expr();
        std::unique_ptr<ExprAST> parse_binop_rhs(int expr_prec, std::unique_ptr<ExprAST> LHS);
        std::unique_ptr<PrototypeAST> parse_prototype();
        std::unique_ptr<FunctionAST> parse_definition();
        std::unique_ptr<FunctionAST> parse_top_level_expr();

        //void handle_definition();
        //void handle_extern();
        void handle_top_level_expression();

        void mainloop();
    private:
        std::string identifier_str;
};