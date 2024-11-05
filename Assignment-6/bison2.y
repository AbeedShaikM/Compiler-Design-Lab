%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern void yyerror(char *s);

%}

/* Token declarations */
%token PLUS MINUS TIMES DIVIDE EQUAL LESS GREATER LPAREN RPAREN LBRACE RBRACE ASSIGN SEMICOLON
%token AND ELSE END IF INT DO FLOAT NOT OR PRINT PROG SCAN STR THEN WHILE
%token ID IC FC

/* Start symbol */
%start P

%%

/* Grammar rules */
P: PROG DL SL END { printf("Valid program\n"); }
    ;

DL: D DL
   | /* epsilon */
   ;

D: TY VL SEMICOLON
  ;

TY: INT
   | FLOAT
   ;

VL: ID VL
   | ID
   ;

SL: S SL
   | /* epsilon */
   ;

S: ES
  | IS
  | WS
  | IOS
  ;

ES: ID ASSIGN E SEMICOLON
   ;

IS: IF BE THEN SL END
   | IF BE THEN SL ELSE SL END
   ;

WS: WHILE BE DO SL END
   ;

IOS: PRINT PE
    | SCAN ID
    ;

PE: E
   | STR
   ;

BE: BE OR AE
   | AE
   ;

AE: AE AND NE
   | NE
   ;

NE: NOT NE
   | LBRACE BE RBRACE
   | RE
   ;

RE: E EQUAL E
   | E LESS E
   | E GREATER E
   ;

E: E PLUS T
  | E MINUS T
  | T
  ;

T: T TIMES F
  | T DIVIDE F
  | F
  ;

F: LPAREN E RPAREN
  | ID
  | IC
  | FC
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