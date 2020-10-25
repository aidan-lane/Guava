%{
  #include <bits/stdc++.h>
  #include "ast.h"
  using namespace std;

  extern "C" int yylex();
%}

%define parse.lac full
%define parse.error verbose

%union {
  struct ast *a;
  int intVal;
  float floatVal;
  struct symbol *s;
  list<symbol*>* symlist;
  int fn;
}

%start program

%token <intVal> INTEGER_LITERAL
%token <floatVal> FLOAT_LITERAL
%token <s> REF;
%token <fn> FUNC;
%token LPAREN RPAREN
%token LCURLY RCURLY
%token COMMA
%token IF THEN ELSE DEFINE

%type <a> expr stmt block list exprlist
%type <symlist> symlist
%left PLUS MINUS
%left MULT DIV MOD
%nonassoc <fn> CMP

%%

program:
  | program stmt { 
      cout << eval($2) << endl;
      free_ast($2);
    }
  | program DEFINE REF LPAREN symlist RPAREN block {
      dodef($3, $5, $7);
    }
  ;

block: 
  LCURLY list RCURLY { $$ = $2; }
  ;

stmt:
  IF expr THEN list             { $$ = new_flow('I', $2, $4, NULL); }
  | IF expr THEN list ELSE list { $$ = new_flow('I', $2, $4, $6); }
  | expr                        { $$ = $1; }
  ;

list:
  /* empty */ { $$ = NULL; }
  | stmt
  ;

expr:
  /* empty */          { $$ = new_num(0); }
  | INTEGER_LITERAL    { $$ = new_num($1); }
  | FLOAT_LITERAL      { $$ = new_num($1); }
  | expr PLUS expr     { $$ = new_ast('+', $1, $3); }
  | expr MINUS expr    { $$ = new_ast('-', $1, $3); }
  | expr MULT expr     { $$ = new_ast('*', $1, $3); }
  | expr DIV expr      { $$ = new_ast('/', $1, $3); }
  | LPAREN expr RPAREN { $$ = $2; }
  | expr CMP expr      { $$ = new_cmp($2, $1, $3); }
  | REF                { $$ = new_ref($1); }
  | FUNC LPAREN exprlist RPAREN { $$ = new_func($1, $3); }
  | REF LPAREN exprlist RPAREN  { $$ = new_call($1, $3); }
  ;

exprlist:
  expr
  | expr COMMA exprlist { $$ = new_ast('L', $1, $3); }
  ;

symlist:
  REF                 { $$ = new list<symbol*>(); $$->push_back($1); }
  | REF COMMA symlist { $$->push_back($1); }
  ;

%%

int main(int argc, char **argv) {
  if (argc < 2) {
    cerr << "Provide a filename!" << endl;
    exit(1);
  }

  FILE *src = fopen(argv[1], "r");
  if (!src) {
    cerr << "Could not open file!" << endl;
    exit(1);
  }

  yyin = src;
  yyparse();
}