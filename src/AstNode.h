#ifndef AST_NODE_H
#define AST_NODE_H

enum NodeType {
    UNDEFINED
};

class AstNode {
public:
    NodeType type;
    double value;
    AstNode* left;
    AstNode* right;

    AstNode(NodeType type, double val, AstNode* left, AstNode* right) 
        : type(type), value(val), left(left), right(right) { }

    ~AstNode() {
        delete left;
        delete right;
    }
};

#endif