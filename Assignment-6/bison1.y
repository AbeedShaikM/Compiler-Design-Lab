%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex();
void yyerror(char *s);

%}

%token ID LPAREN RPAREN PLUS TIMES

%start E

%%

E: T 
  | E PLUS T 
  ;

T: F 
  | T TIMES F 
  ;

F: ID 
  | LPAREN E RPAREN
  ;

%%

extern int yylex();
extern int yyparse();
extern int line_num;

void yyerror(char *s) {
    printf("Error: %s at line %d\n", s, line_num);
    exit(-1);
}

int main() {
    yyparse();
    printf("Accepted\n");
    return 0;
}