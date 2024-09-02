%{
#include <stdio.h>
%}

%%
(0*1|1)(0*1|1)(0*1|1)(0*1|1)(0*1|1)(0*1|1)[0-1]*  { return id;}
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