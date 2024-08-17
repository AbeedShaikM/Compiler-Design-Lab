%{
#include <stdio.h>
int length = 0, flag = 0;
%}

%%
aa {flag = 1;length += 2; }
bb {flag = 1;length += 2; }
a|b|c {length++; }
\n      {return 0;}
EXIT    {exit(1);}
.       { printf("Invalid input\n");exit(1);}
%%

int main() {
    printf("Enter string:\n");
    yylex();
    if(length == 6 && flag){
      printf("Valid\n");
    }
    else{
      printf("Invalid\n");
    }
    return 0;
}

int yywrap() {
    return 1;
}

