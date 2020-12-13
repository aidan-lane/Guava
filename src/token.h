#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>

using namespace std;

enum TokenType {
    Error,
    Plus,
    Minus,
    Mul,
    Div,
    Number,
    OParen,
    CParen
};

class Token {
public:
    TokenType type;
    double val;

    Token(TokenType type, double val) : type(type), val(val) {}
    void print();
};

#endif