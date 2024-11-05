%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
"scan"           { return SCAN;}
"str"            { return STR; }
"then"           { return THEN; }
"while"          { return WHILE;}

[0-9]+           { return IC; } 
[0-9]+\.[0-9]+   { return FC; }  
\"[^\"]*\"       { return STR; }  
[a-zA-Z_][a-zA-Z0-9_]* { return ID;}
[ \t]         { /* Ignore whitespace */ }
[\n]          {line_num++;}
.                {  yyerror("Invalid Character\n");} 
%%

int yywrap(void) {return 1;}