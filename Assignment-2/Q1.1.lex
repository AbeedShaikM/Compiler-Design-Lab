%{
#include <stdio.h>

int one_count = 0;
%}

%%
(0*1|1)(0*1|1)(0*1|1)(0*1|1)(0*1|1)(0*1|1)[0-1]*  { printf("valid\n"); return 1;}
\n      {}
EXIT    {exit(1);}
.       { printf("Invalid input\n");exit(1);}
%%

int main() {
    printf("Enter binary string:\n");
    yylex();

    return 0;
}

int yywrap() {
    return 1;
}
