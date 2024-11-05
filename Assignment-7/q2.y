%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
extern char* yytext;
%}

%union {
    double val;
}

%token <val> NUMBER
%type <val> S E T F
%left '-' '+' '*' '/'
%right UMINUS

%%

S: E { printf("Result = %lf\n", $1); }
;

E: E '+' T { $$ = $1 + $3; }
 | E '-' T { $$ = $1 - $3; }
 | T       { $$ = $1; }
;

T: T '*' F { $$ = $1 * $3; }
 | T '/' F { if ($3 == 0) {
                yyerror("Division by zero error");
                YYABORT;
            }
            $$ = $1 / $3;
          }
 | F       { $$ = $1; }
;

F: '(' E ')' { $$ = $2; }
 | '-' F %prec UMINUS { $$ = -$2; }  // Handle unary minus
 | NUMBER { $$ = $1; }
;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
    printf("Enter an arithmetic expression:\n");
    if(yyparse() == 0) ;
    return 0;
}
