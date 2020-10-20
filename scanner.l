%option noyywrap

%{
  #include <iostream>
  #include "parser.c"
  extern "C" void yyerror(char const*);
  using namespace std;
%}

%%

[ \t\r\v\f]    ; /* whitespace */
[\n]           { yylineno++; }  ; /* increment line number */
[0-9]+         { yylval.intVal = atoi(yytext); return INTEGER_LITERAL; }
[0-9]+.[0-9]+  { yylval.floatVal = atof(yytext); return FLOAT_LITERAL; }
"+"            { return PLUS; }
"-"            { return MINUS; }
"*"            { return MULT; }
"/"            { return DIV; }
"{"            { return OPEN_BRACKET; }
"}"            { return CLOSE_BRACKET; }
"("            { return OPEN_PAREN; }
")"            { return CLOSE_PAREN; }

"main"         { return MAIN_FUNCTION; }

%%

void yyerror(char const *s) {
  cout << "ERROR ON LINE:" << yylineno << " " << string(s) << endl;
  exit(0);
}