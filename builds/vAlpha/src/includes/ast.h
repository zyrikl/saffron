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

#include <string>
#include <memory>
#include <vector>

class ExprAST {
    public:
        virtual ~ExprAST() = default;
};

class NumberExprAST : public ExprAST {
    double value;

    public:
        NumberExprAST(double value);
};

class VariableExprAST : public ExprAST {
    std::string name;

    public:
        VariableExprAST(std::string name);
};

class BinaryExprAST : public ExprAST {
    char Op;
    std::unique_ptr<ExprAST> LHS, RHS;

    public:
        BinaryExprAST(char Op, std::unique_ptr<ExprAST> LHS, std::unique_ptr<ExprAST> RHS);
};

class UnaryExprAST : public ExprAST {
    char Op;
    std::unique_ptr<ExprAST> Operand;

    public:
        UnaryExprAST(char Op, std::unique_ptr<ExprAST> Operand);
};

// Function calls expression
class CallExprAST : public ExprAST {
    std::string callee;
    std::vector<std::unique_ptr<ExprAST>> args;

    public:
        CallExprAST(std::string callee, std::vector<std::unique_ptr<ExprAST>> args);
};

// Prototype for function expression
class PrototypeAST {
    std::string name;
    std::vector<std::string> args;

    public:
        PrototypeAST(std::string name, std::vector<std::string> args);
        std::string get_name();
};

class FunctionAST {
    std::unique_ptr<PrototypeAST> proto;
    std::unique_ptr<ExprAST> body;

    public:
        FunctionAST(std::unique_ptr<PrototypeAST> proto, std::unique_ptr<ExprAST> body);
};