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
    CParen,
    Name,
    String
};

class Token {
public:
    TokenType type;
    double val;
    string symbol;

    Token(TokenType type, double val) :
        type(type), val(val), symbol("") {}
    Token(TokenType type, double val, string symbol) : 
        type(type), val(val), symbol(symbol) {}
    void print();
};

#endif