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

#include "parser.h"
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <cstdio>
#include "ast.h"
#include "token.h"
#include "error.h"

Parser::Parser(std::vector<Token> tokens) : tokens(std::move(tokens)) {}

Token Parser::get_next_token() {
    current_token = tokens[current_token_number++];
    identifier_str = current_token.lexeme;
    // debug stuff
    //std::cout << current_token.lexeme << std::endl;
    return current_token;
}

int Parser::get_token_precedence() {
    return binop_precedence[current_token.type];
}

std::unique_ptr<ExprAST> Parser::parse_number_expr() {
    auto result = std::make_unique<NumberExprAST>(std::any_cast<double>(current_token.literal));
    get_next_token();
    return std::move(result);
}

std::unique_ptr<ExprAST> Parser::parse_paren_expr() {
    get_next_token();
    auto v = parse_expression();
    if (!v) {
        return nullptr;
    }

    if (current_token.type != token::RIGHT_PAREN) {
        error::error_log("Expected ')' in expression.");
    }

    get_next_token();
    return v;
}

std::unique_ptr<ExprAST> Parser::parse_identifier_expr() {
    std::string id_name = current_token.lexeme;

    get_next_token();

    if (current_token.type != token::LEFT_PAREN) return std::make_unique<VariableExprAST>(id_name);

    get_next_token();
    std::vector<std::unique_ptr<ExprAST>> args;
    if (current_token.type != token::RIGHT_PAREN) {
        while (true) {
            if (auto arg = parse_expression()) {
                args.push_back(std::move(arg));
            } else {
                return nullptr;
            }

            if (current_token.type == token::RIGHT_PAREN) {
                break;
            }

            if (current_token.type != token::COMMA) {
                error::error_log("Expected ')' or ',' in function argument list.");
            }

            get_next_token();
        }
    }

    get_next_token();
    return std::make_unique<CallExprAST>(id_name, std::move(args));
}

std::unique_ptr<ExprAST> Parser::parse_primary() {
    switch (current_token.type) {
        case token::IDENTIFIER:
            return parse_identifier_expr();
        case token::NUMBER:
            return parse_number_expr();
        case token::LEFT_PAREN:
            return parse_paren_expr();
        default:
            error::error_log("Expected expression, received unknown.");
            return nullptr;
            //break;
    }
}

std::unique_ptr<ExprAST> Parser::parse_binop_rhs(int expr_prec, std::unique_ptr<ExprAST> LHS) {
    while (true) {
        int token_prec = get_token_precedence();

        if (token_prec < expr_prec) return LHS;

        // maybe won't need this
        Token binop = current_token;
        get_next_token();

        auto RHS = parse_primary();
        if (!RHS) return nullptr;

        int next_prec = get_token_precedence();
        if (token_prec < next_prec) {
            RHS = parse_binop_rhs(token_prec + 1, std::move(RHS));
            if (!RHS) return nullptr;
        }

        LHS = std::make_unique<BinaryExprAST>(binop.type, std::move(LHS), std::move(RHS));
    }
}

// I love how descriptive my comments from yesterday are:
//      |
//      |
//      |
//     \|/
//      '
// something here down later
std::unique_ptr<ExprAST> Parser::parse_expression() {
    auto LHS = parse_primary();
    if (!LHS) {
        return nullptr;
    }
    return parse_binop_rhs(0, std::move(LHS));
}

std::unique_ptr<PrototypeAST> Parser::parse_prototype() {
    if (current_token.type != token::IDENTIFIER) {
        error::error_log("Expected a function name, not whatever you gave me.");
    }

    std::string fn_name = current_token.lexeme;
    get_next_token();

    if (current_token.type != token::LEFT_PAREN) {
        error::error_log("Function needs '('.");
    }

    std::vector<std::string> arg_names;
    while (get_next_token().type == token::IDENTIFIER) {
        arg_names.push_back(identifier_str);
    }

    if (current_token.type != token::RIGHT_PAREN) {
        error::error_log("Function needs ')'.");
    }

    get_next_token();

    return std::make_unique<PrototypeAST>(fn_name, std::move(arg_names));
}

std::unique_ptr<FunctionAST> Parser::parse_definition() {
    get_next_token();
    auto proto = parse_prototype();
    if (!proto) return nullptr;

    if (auto E = parse_expression()) {
        return std::make_unique<FunctionAST>(std::move(proto), std::move(E));
    }
    return nullptr;
}

std::unique_ptr<FunctionAST> Parser::parse_top_level_expr() {
    if (auto E = parse_expression()) {
        auto proto = std::make_unique<PrototypeAST>("__anon_expr", std::vector<std::string>());
        return std::make_unique<FunctionAST>(std::move(proto), std::move(E));
    }
    return nullptr;
}

void Parser::handle_top_level_expression() {
    if (parse_top_level_expr()) {
        fprintf(stderr, "Parsed a top-level expr\n");
    } else {
        get_next_token();
    }
}

void Parser::mainloop() {
    while (true) {
        //get_next_token();
        switch (current_token.type) {
            case token::EOF_TOKEN:
                return;
            case token::NEWLINE:
                get_next_token();
                break;
            default:
                handle_top_level_expression();
                break;
        }
    }
}