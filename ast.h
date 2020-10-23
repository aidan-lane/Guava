/*
 * Abstract Syntax Tree implementation
 */

extern int yylineno;
void yyerror(char const *s, ...);

struct ast {
  int nodetype;
  struct ast *l;
  struct ast *r;
};

struct numval {
  int nodetype;
  float number;
};

struct ast *new_ast(int nodetype, struct ast *l, struct ast *r);
struct ast *new_num(float val);

float eval(struct ast *);
void free_ast(struct ast *);