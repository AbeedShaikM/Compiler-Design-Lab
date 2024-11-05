%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h" // Include the Bison header file

extern int yylex(); // Declare yylex from Bison
extern void yyerror(const char *s); // Declare yyerror from Bison

int line_num = 1;
%}

%%

"(" {return LPAREN;}
")" {return RPAREN;}
"+" {return PLUS;}
"*" {return TIMES;}
[0-9]+ {return ID;}
[a-zA-Z_][a-zA-Z0-9_]* {
  return ID; 
}
[ \t] {}
[\n] {line_num++;}
.      { yyerror("Invalid Character\n");} 

%%


int yywrap(void) {return 1;}
