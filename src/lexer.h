#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <list>
#include "../include/mio/mio.hpp"
#include "token.h"

using namespace std;

class Lexer {
public:
    list<Token>* lex(const string& path);
    int handle_error(const error_code& error);
    void print_tokens();

private:
    list<Token> tokens;
    int lineno, colno;
};

#endif