%option noyywrap

%{
  #include <iostream>
  #include "parser.cpp"
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
"{"            { return LCURLY; }
"}"            { return RCURLY; }
"("            { return LPAREN; }
")"            { return RPAREN; }
","            { return COMMA; }
#.             ; /* comment */
.              { yyerror("Invalid Character %c\n", *yytext); }

"main"         { return MAIN_FUNCTION; }

%%