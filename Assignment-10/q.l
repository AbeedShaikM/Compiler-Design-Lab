%{
#include <bits/stdc++.h>
using namespace std;
#include "y.tab.h"
int line_num = 1;
%}

%%
"+"              { return PLUS; }
"-"              { return MINUS; }
"*"              { return TIMES; }
"/"              { return DIVIDE; }
"="              { return EQUAL; }
"<"              { return LESS; }
">"              { return GREATER; }
"("              { return LPAREN; }
")"              { return RPAREN; }
"{"              { return LBRACE; }
"}"              { return RBRACE; }
":="             { return ASSIGN; }
";"              { return SEMICOLON; }
"and"            { return AND; }
"else"           { return ELSE; }
"end"            { return END; }
"if"             { return IF; }
"int"            { return INT; }
"do"             { return DO; }
"float"          { return FLOAT; }
"not"            { return NOT; }
"or"             { return OR; }
"print"          { return PRINT; }
"prog"           { return PROG; }
"scan"           { return SCAN; }
"str"            { return STR; }
"then"           { return THEN; }
"while"          { return WHILE; }

[0-9]+           { yylval.id = new string(yytext); return IC; }  /* Integer literal */
[0-9]+\.[0-9]+   { yylval.id = new string(yytext); return FC; }  /* Floating-point literal */
\"[^\"]*\"       { yylval.id = new string(yytext); return STR; }  /* String literal */
[a-zA-Z_][a-zA-Z0-9_]* { yylval.id = new string(yytext); return ID; }
[ \t\n]+         { /* Ignore whitespace */ }

.                { fprintf(yyout, "UNKNOWN"); }  /* Catch-all for any other character */
%%

int yywrap(void) { return 1; }
