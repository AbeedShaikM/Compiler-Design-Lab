%{
#include "ast.h"  // Include the shared declarations for Node
#include "y.tab.h"
%}

%%
[ \t]+               ;  
[a-zA-Z][a-zA-Z0-9]*    { yylval.id = yytext; return ID; }
[0-9]+                  { yylval.id = yytext; return ID; }
"+"                    { return PLUS; }
"-"                    { return MINUS; }
"*"                    { return MUL; }
"/"                    { return DIV; }
"("                    { return LPAREN; }
")"                    { return RPAREN; }
"$"                    { return DOLLAR; } 
"="                      { return 0; }

%%

int yywrap() {
    return 1;
}
