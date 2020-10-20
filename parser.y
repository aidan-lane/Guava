%{
  #include <iostream>
  using namespace std;
  extern "C" void yyerror(char *s);
  extern "C" int yyparse();
%}

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
  | MAIN_FUNCTION OPEN_PAREN CLOSE_PAREN OPEN_BRACKET statement CLOSE_BRACKET { cout << $5 << endl; }
  ;

statement: exp

exp:
  INTEGER_LITERAL { $$ = $1; }
  | FLOAT_LITERAL { $$ = $1; }
  | exp PLUS exp  { $$ = $1 + $3; }

%%

int main(int argc, char **argv) {
  if (argc < 2) {
    cout << "Provide a filename!" << endl;
    exit(1);
  }

  FILE *src = fopen(argv[1], "r");
  if (!src) {
    cout << "Could not open file!" << endl;
    exit(1);
  }

  yyin = src;
  yyparse();
}

void yyerror(char *s) {
  fprintf(stderr, "%s\n", s);
}