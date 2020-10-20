%option noyywrap

%{
  #include <iostream>
  #include "parser.cpp"
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
"{"            { return O_CURLY; }
"}"            { return C_CURLY; }
"("            { return O_PAREN; }
")"            { return C_PAREN; }

"main"         { return MAIN_FUNCTION; }

%%

void yyerror(char const *s) {
  cout << "ERROR ON LINE:" << yylineno << " " << string(s) << endl;
  exit(0);
}