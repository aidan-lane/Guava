#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <list>
#include "token.h"
#include "AstNode.h"

using namespace std;

/**
 * Language CFG:
 * 
 * PROGRAM -> EXP
 * EXP     -> TERM EXP1
 * EXP1    -> + TERM EXP1 |
 *            - TERM EXP1 |
 *            eps
 * TERM    -> FACTOR TERM1
 * TERM1   -> * FACTOR TERM1 |
 *            / FACTOR TERM1 |
 *            eps
 * FACTOR  -> ( EXP ) | - EXP | number
 **/

class Parser {
public:
    AstNode* parse(list<Token>& tokens);

private:
    AstNode* program();
    AstNode* exp();
    AstNode* exp1();
    AstNode* term;
    AstNode* term1;
    AstNode* factor();
};

#endif