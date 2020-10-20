%option noyywrap

%{
  extern "C" int yylex();
  #include "parser.c"
  using namespace std;
%}

%%

[ \n\t\r\f]+       ; /* ignore whitespace */
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
","            cout << "COMMA" << endl;
[a-z][a-zA-Z]* cout << "LOWER" << endl;

%%