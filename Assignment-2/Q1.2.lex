%{
#include <stdio.h>
%}

%%
aa*(b|c)*a    { printf(" T1 "); }
bb*(a|c)*b    { printf(" T2 "); }
cc*(b|a)*c    { printf(" T3 "); }
.|\n          { printf(" ? "); }
%%

int main() {
    printf("Enter string:\n");
    yylex();

    return 0;
}

int yywrap() {
    return 1;
}

