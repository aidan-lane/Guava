#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <list>

using namespace std;

class Lexer {
public:
    void lex(const string& path);
    void clear();

private:
    list<int> tokens;
};

#endif