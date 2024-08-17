%{
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to ignore illegal symbols within numbers
void print_ignored_number(const char* yytext) {
    int len = strlen(yytext);
    printf("Integer (illegal symbol ");
    for (int i = 1; i < len; ++i) {
        if (!isdigit(yytext[i])) {
            printf("%c", yytext[i]);
        }
    }
    printf(" will be ignored)\n");
}

void is_valid_character(const char* yytext){
    int len = strlen(yytext);
    if(len == 3){
        printf("Character constant\n");
    }
    else{
        printf("Invalid\n");
    }
}
%}

%%
[+-]?[0-9]+\.[0-9]+    { printf("Float\n");}
[+-]?[0-9]+            { printf("Integer\n"); }
[^0-9\s\n\']*[+-]?[^0-9\s\n\'\"]*[0-9]+(.*)  { print_ignored_number(yytext); }
\'[^\']*\'              { is_valid_character(yytext);}
\"[^\"]*\"             { printf("String constant\n"); }
.*                     { printf("Invalid\n");}

%%

int main(int argc, char **argv)
{
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}