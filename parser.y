%{
  #include <bits/stdc++.h>
  #include "Headers/ast.h"
  using namespace std;

  extern "C" void yyerror(char const*);
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

%type <floatVal> exp
%type <floatVal> statement
%left PLUS MINUS
%left MULT DIV MOD

%%

program:
  | MAIN_FUNCTION LPAREN RPAREN LCURLY statement RCURLY { cout << $5 << endl; }
  ;

statement: exp

exp:
  | INTEGER_LITERAL     { $$ = $1; }
  | FLOAT_LITERAL       { $$ = $1; }
  | exp PLUS exp        { $$ = $1 + $3; }
  | exp MINUS exp       { $$ = $1 - $3; }
  | exp MULT exp        { $$ = $1 * $3; }
  | exp DIV exp         { $$ = $1 / $3; }
  | LPAREN exp RPAREN   { $$ = $2; }
  | FUNC LPAREN args RPAREN 

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