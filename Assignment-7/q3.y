%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function prototype for the lexer
int yylex(void);
void yyerror(const char *s);
%}

%union {
    double val;
}

// Define token types
%token <val> NUMBER
%token SQRT LOG LOG10 SIN COS TAN
%token PI EULER

%left '+' '-' '*' '/' 
%right '^'  // Right associative for exponentiation
%right UMINUS // Unary minus

%type <val> S E T F

%%

// Grammar rules and actions
S: E { printf("Result = %lf\n", $1); }
;

E: E '+' T { $$ = $1 + $3; }
 | E '-' T { $$ = $1 - $3; }
 | T       { $$ = $1; }
 ;

T: T '*' F { $$ = $1 * $3; }
 | T '/' F { 
      if ($3 == 0) {
          yyerror("Division by zero error");
          YYABORT;
      }
      $$ = $1 / $3; 
 }
 | T '^' F { $$ = pow($1, $3); } // Exponentiation
 | F       { $$ = $1; }
 ;

F: '(' E ')' { $$ = $2; }
 | '-' F %prec UMINUS { $$ = -$2; }  // Handle unary minus
 | SQRT '(' E ')' { $$ = sqrt($3); }
 | LOG '(' E ')' { $$ = log($3); }
 | LOG10 '(' E ')' { $$ = log10($3); }
 | SIN '(' E ')' { $$ = sin($3); }
 | COS '(' E ')' { $$ = cos($3); }
 | TAN '(' E ')' { $$ = tan($3); }
 | NUMBER { $$ = $1; }
 | PI { $$ = M_PI; }
 | EULER { $$ = M_E; }
 ;

%%

// Error handling function
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

// Main function
int main(void) {
    printf("Enter an arithmetic expression:\n");
    if (yyparse() == 0) {
        printf("Parsing completed successfully.\n");
    }
    return 0;
}
