#include <string>
#include <iostream>
#include <cctype>
#include <cstdio>
#include <unordered_map>

std::string code;

enum token { EOF_TOKEN, NUMBER, PLUS, MINUS, MULTIPLY, DIVIDE };
std::string token_value;
std::string peek_value;

int current = 0;
int start = 0;

token get_next_token(bool peek = false) {
    int lc = current; // local carbon copy
    int ls = start;

    int *c = peek ? &lc : &current;
    int *s = peek ? &ls : &start;

    while (*c < code.length()) {
        *s = *c;

        switch (code[*c]) {
            case ' ':
                (*c)++;
                continue;
            case '+':
                (*c)++;
                return PLUS;
            case '-':
                (*c)++;
                return MINUS;
            case '*':
                (*c)++;
                return MULTIPLY;
            case '/':
                (*c)++;
                return DIVIDE;
            default:
                if (std::isdigit(code[*c])) {
                    while (*c < code.length() && std::isdigit(code[*c]))
                        (*c)++;

                    token_value = code.substr(*s, *c - *s);
                    return NUMBER;
                }
                break;
        }

        current++;
    }

    return EOF_TOKEN;
}

std::unordered_map<token, int> binding_powers = {
    { EOF_TOKEN, 0  },
    { PLUS,      10 },
    { MINUS,     10 },
    { MULTIPLY,  20 },
    { DIVIDE,    20 }
};

int get_bp(token t) {
    if (binding_powers.find(t) != binding_powers.end()) {
        return binding_powers.find(t)->second;
    } else {
        return 0;
    }
}

double parse_expression(int binding_power = 0);

double nud(token t) {
    switch (t) {
        case NUMBER:
            return std::stod(token_value);
        default:
            std::cerr << "Invalid token in front." << std::endl;
            std::exit(1);
            break;
    }
}

double led(token t, double left) {
    double right = parse_expression(get_bp(t));

    switch (t) {
        case PLUS:
            return left + right;
        case MINUS:
            return left - right;
        case MULTIPLY:
            return left * right;
        case DIVIDE:
            return left / right;
        default:
            std::cerr << "Unknown operator/operation." << std::endl;
            std::exit(1);
            break;
    }
}

double parse_expression(int binding_power) {
    token t = get_next_token();
    double l = nud(t);

    while (true) {
        token next = get_next_token(true);
        if (next == EOF_TOKEN) break;
            
        int next_bp = get_bp(next);
        if (next_bp <= binding_power) break;

        t = get_next_token();
        l = led(t, l);
    }

    return l;
}

int main() {

    std::cout << "Type \"exit\" to escape." << std::endl;

    while (true) {
        std::cout << "Calculate: ";
        std::getline(std::cin, code);

        if (code == "exit") break;
        std::cout << parse_expression() << std::endl;
        
        // reset vars for next parse
        current = 0;
        start = 0;
    }

    return 0;
}
