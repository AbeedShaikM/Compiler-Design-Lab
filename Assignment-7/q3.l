%{
#include "y.tab.h"  // Required to use YACC token definitions
#include <stdlib.h> // Required for atof
#include <math.h>   // Required for mathematical functions

// Declare yylval as an external variable
extern YYSTYPE yylval;
%}

%%

"sqrt"             { return SQRT; }
"log10"            { return LOG10; }
"log"              { return LOG; }
"sin"              { return SIN; }
"cos"              { return COS; }
"tan"              { return TAN; }
"pi"               { return PI; }       // Return PI token
"e"                { return EULER; }    // Return EULER token

[0-9]+(\.[0-9]+)?  { yylval.val = atof(yytext); return NUMBER; }

[ \t\n]+           ;                   

"+"                { return '+'; }
"-"                { return '-'; }
"*"                { return '*'; }
"/"                { return '/'; }
"^"                { return '^'; }      // Exponentiation operator (escaped ^)
"("                { return '('; }
")"                { return ')'; }
"="                { return 0; }        // Return '=' token if needed
.                  { printf("Unknown character: %s\n", yytext); }

%%

int yywrap(void) {
    return 1;
}
