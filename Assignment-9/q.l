%{  // Include the shared declarations for Node
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"
%}

%%
[ \t]+               ;  // Ignore whitespace and newlines
[a-zA-Z][a-zA-Z0-9]*    { yylval.id = strdup(yytext); return ID; }
"+"                    { return PLUS; }
"-"                    { return MINUS; }
"*"                    { return MULT; }
"/"                    { return DIV; }
"("                    { return LPAREN; }
")"                    { return RPAREN; }
"$"                    { return DOLLAR; } 

%%

int yywrap() {
    return 1;
}
