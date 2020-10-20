%{
  #include <stdio.h>
  #include <string.h>

  extern "C" void yyerror(char const*);
  extern "C" int yylex();
%}

%define parse.lac full
%define parse.error verbose

%union{
  int intVal;
  float floatVal;
}

%start main

%token MAIN_FUNCTION
%token <intVal> INTEGER_LITERAL
%token <floatVal> FLOAT_LITERAL
%token OPEN_PAREN
%token CLOSE_PAREN
%token OPEN_BRACKET
%token CLOSE_BRACKET

%type <floatVal> exp
%type <floatVal> statement
%left PLUS MINUS
%left MULT DIV MOD

%%

main:
  | MAIN_FUNCTION OPEN_PAREN CLOSE_PAREN OPEN_BRACKET statement CLOSE_BRACKET { printf("%f\n", $5); }
  ;

statement: exp

exp:
  INTEGER_LITERAL { $$ = $1; }
  | FLOAT_LITERAL { $$ = $1; }
  | exp PLUS exp  { $$ = $1 + $3; }

%%

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Provide a filename!\n");
    exit(1);
  }

  FILE *src = fopen(argv[1], "r");
  if (!src) {
    printf("Could not open file!\n");
    exit(1);
  }

  yyin = src;
  yyparse();
}