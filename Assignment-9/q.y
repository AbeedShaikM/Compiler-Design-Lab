%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int temp_counter = 0;
char temp[10];

char* newtemp() {
    sprintf(temp, "t%d", temp_counter++);
    return strdup(temp);
}

void gen(char* op, char* arg1, char* arg2, char* result) {
    printf("%s = %s %s %s\n", result, arg1, op, arg2);
}

void yyerror(const char *s);
int yylex(void);

%}

%union {
    char* id;
}

%token <id> ID
%token PLUS MINUS MULT DIV LPAREN RPAREN DOLLAR
%type <id> E T F

%%

input:
    E DOLLAR { printf("3-address code generation completed.\n"); return 0; }
;

E:
    E PLUS T { 
        char* temp = newtemp();
        gen("+", $1, $3, temp);
        $$ = temp;
    }
  | E MINUS T {
        char* temp = newtemp();
        gen("-", $1, $3, temp);
        $$ = temp;
    }
  | T { $$ = $1; }
;

T:
    T MULT F { 
        char* temp = newtemp();
        gen("*", $1, $3, temp);
        $$ = temp;
    }
  | T DIV F { 
        char* temp = newtemp();
        gen("/", $1, $3, temp);
        $$ = temp;
    }
  | F { $$ = $1; }
;

F:
    LPAREN E RPAREN { $$ = $2; }
  | ID { $$ = $1; }
;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
    yyparse();
    return 0;
}

