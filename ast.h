#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <bits/stdc++.h>

using namespace std;

extern int yylineno;
void yyerror(char const *s, ...);

/*
 * Symbol Table Definitions
 */

struct symbol {
  string name;
  float value;
  struct ast *func;
  list<struct symbol *>* symlist;
};

struct symbol *lookup(char*);

void free_list(list<symbol*>*);

enum builtins {
  B_sqrt = 1,
  B_exp,
  B_log,
};

/*
 * Abstract Syntax Tree Definitions
 */

/* Generic ast structure */
struct ast {
  int nodetype;
  struct ast *l;
  struct ast *r;
};

/* built-in function*/
struct fncall {
  int nodetype; // 'F'
  struct ast *l;
  enum builtins functype;
};

/* user-defined function*/
struct ufncall {
  int nodetype; // 'C'
  struct ast *l;
  struct symbol *s;
};

struct flow {
  int nodetype; // 'I'
  struct ast *cond;
  struct ast *tl;
  struct ast *el;
};

struct symref {
  int nodetype; // 'N'
  struct symbol *s;
};

struct numval {
  int nodetype;
  float number;
};

struct ast *new_ast(int nodetype, struct ast *l, struct ast *r);
struct ast *new_cmp(int cmptype, struct ast *l, struct ast *r);
struct ast *new_func(int functype, struct ast *l);
struct ast *new_call(struct symbol *s, struct ast *l);
struct ast *new_ref(struct symbol *s);
struct ast *new_flow(int nodetype, struct ast *cond, struct ast *tl, struct ast *el);
struct ast *new_num(float val);

static float call_builtin(struct fncall *);
static float call_user(struct ufncall *);
void dodef(struct symbol *name, list<symbol*>* symlist, struct ast *stmts);

float eval(struct ast *);
void free_ast(struct ast *);