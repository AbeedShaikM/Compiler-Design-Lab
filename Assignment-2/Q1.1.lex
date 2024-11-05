%{
#include <stdio.h>

int one_count = 0;
%}

%%
"(" {return "(";}
")" {return ")";}
"+" {return "+";}
"*" {return "*";}
[a-zA-Z_][a-zA-Z0-9_]* {  // Use yylval.str for string storage
  printf("aa\n"); 
}
[ \t] {}
[\n] {return 0;}
.*       { printf("1\n");} // Call yyerror function

%%

int main() {
    printf("Enter binary string:\n");
    yylex();

    return 0;
}

int yywrap() {
    return 1;
}
