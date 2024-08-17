%{
#include <stdio.h>
%}

%%
c[a-zA-Z0-9]*r { printf("valid\n"); return 1;}
.*       { printf("Invalid input\n");exit(1);}
%%

int main() {
    printf("Enter string:\n");
    yylex();

    return 0;
}

int yywrap() {
    return 1;
}

