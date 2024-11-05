%{
#include "y.tab.h"  
#include <stdlib.h> 

%}

%%
\/\*([^*]|\*+[^*/])*\*+\/    { printf("Comments\n"); }
\/\/([^\n])* {printf("Comment\n");}
[0-9]+(\.[0-9]+)?  { yylval.val = atof(yytext); return NUMBER; }  
[ \t\n]+           ;                   
"+"                { return '+'; }
"-"                { return '-'; }
"*"                { return '*'; }
"/"                { return '/'; }
"("                { return '('; }
")"                { return ')'; }
"="                { return 0; }
.                  { printf("Unknown character: %s\n", yytext); }

%%

int yywrap(void) {
    return 1;
}
