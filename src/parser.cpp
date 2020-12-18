#include "parser.h"

AstNode* Parser::parse(list<Token>& tokens)
{

}

AstNode* Parser::program()
{
    AstNode* root = exp();
    return new AstNode(UNDEFINED, 0, root, nullptr);
}

AstNode* Parser::exp()
{
    
}

AstNode* Parser::program()
{
    
}

AstNode* Parser::program()
{
    
}