%{
#include "ast.h"  // Include the shared declarations for Node

void yyerror(const char *s);
int yylex(void);
%}

// Declare the union to handle different types of values (for tokens and non-terminals)
%union {
    char *id;  // For identifiers (ID)
    Node *node;  // For AST nodes
}

// Declare token types and non-terminal types
%token <id> ID
%token PLUS MINUS MUL DIV LPAREN RPAREN DOLLAR
%type <node> expr term factor

%%

// Grammar rules and semantic actions

input:
    expr DOLLAR { printAST($1, 0); return 0; }
    ;

expr:
      expr PLUS term  { $$ = createNode("+", $1, $3); }
    | expr MINUS term { $$ = createNode("-", $1, $3); }
    | term            { $$ = $1; }
    ;

term:
      term MUL factor { $$ = createNode("*", $1, $3); }
    | term DIV factor { $$ = createNode("/", $1, $3); }
    | factor          { $$ = $1; }
    ;

factor:
      LPAREN expr RPAREN { $$ = $2; }
    | ID                 { $$ = createNode($1, NULL, NULL); }
    ;
%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
    printf("Enter an expression: ");
    if (yyparse() == 0) {
        printf("Parsing completed successfully.\n");
        return 0;
    }
    else {
        printf("Parsing failed.\n");
        return 1;
    }
    return yyparse();
}
