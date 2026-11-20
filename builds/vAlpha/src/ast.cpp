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

#include "ast.h"
#include <string>
#include <memory>
#include <vector>

NumberExprAST::NumberExprAST(double value) : value(value) {}

VariableExprAST::VariableExprAST(const std::string name) : name(name) {}

BinaryExprAST::BinaryExprAST(char Op, std::unique_ptr<ExprAST> LHS, std::unique_ptr<ExprAST> RHS) : Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}

UnaryExprAST::UnaryExprAST(char Op, std::unique_ptr<ExprAST> Operand) : Op(Op), Operand(std::move(Operand)) {}

CallExprAST::CallExprAST(std::string callee, std::vector<std::unique_ptr<ExprAST>> args) : callee(callee), args(std::move(args)) {}

PrototypeAST::PrototypeAST(std::string name, std::vector<std::string> args) : name(name), args(std::move(args)) {}
std::string PrototypeAST::get_name() { return name; }

FunctionAST::FunctionAST(std::unique_ptr<PrototypeAST> proto, std::unique_ptr<ExprAST> body) : proto(std::move(proto)), body(std::move(body)) {}