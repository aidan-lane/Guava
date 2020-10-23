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
}

%start program

%token MAIN_FUNCTION
%token <intVal> INTEGER_LITERAL
%token <floatVal> FLOAT_LITERAL
%token LPAREN RPAREN
%token LCURLY RCURLY
%token COMMA

%type <a> exp
%type <a> statement
%left PLUS MINUS
%left MULT DIV MOD

%%

program:
  | MAIN_FUNCTION LPAREN RPAREN LCURLY statement RCURLY 
  { 
    cout << eval($5) << endl;
    free_ast($5);
  }
  ;

statement: exp

exp:
  INTEGER_LITERAL       { $$ = new_num($1); }
  | FLOAT_LITERAL       { $$ = new_num($1); }
  | exp PLUS exp        { $$ = new_ast('+', $1, $3); }
  | exp MINUS exp       { $$ = new_ast('-', $1, $3); }
  | exp MULT exp        { $$ = new_ast('*', $1, $3); }
  | exp DIV exp         { $$ = new_ast('/', $1, $3); }
  | LPAREN exp RPAREN   { $$ = $2; }
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