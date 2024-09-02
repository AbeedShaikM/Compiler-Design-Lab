%{
#include <stdio.h>
#include <stdlib.h>

FILE *yyin;  // Input file
FILE *yyout; // Output file
%}

%%
"+"              { fprintf(yyout, "+"); }
"−"              { fprintf(yyout, "−"); }
"∗"              { fprintf(yyout, "∗"); }
"/"              { fprintf(yyout, "/"); }
"="              { fprintf(yyout, "="); }
"<"              { fprintf(yyout, "<"); }
">"              { fprintf(yyout, ">"); }
"("              { fprintf(yyout, "("); }
")"              { fprintf(yyout, ")"); }
"{"              { fprintf(yyout, "{"); }
"}"              { fprintf(yyout, "}"); }
":="             { fprintf(yyout, ":="); }
";"              { fprintf(yyout, ";"); }
"and"            { fprintf(yyout, "and"); }
"else"           { fprintf(yyout, "else"); }
"end"            { fprintf(yyout, "end"); }
"if"             { fprintf(yyout, "if"); }
"int"            { fprintf(yyout, "int"); }
"do"             { fprintf(yyout, "do"); }
"float"          { fprintf(yyout, "float"); }
"not"            { fprintf(yyout, "not"); }
"or"             { fprintf(yyout, "or"); }
"print"          { fprintf(yyout, "print"); }
"prog"           { fprintf(yyout, "prog"); }
"scan"           { fprintf(yyout, "scan"); }
"str"            { fprintf(yyout, "str"); }
"then"           { fprintf(yyout, "then"); }
"while"          { fprintf(yyout, "while"); }

[0-9]+           { fprintf(yyout, "ic"); }  /* Integer literal */
[0-9]+\.[0-9]+   { fprintf(yyout, "fc"); }  /* Floating-point literal */
\"[^\"]*\"       { fprintf(yyout, "str"); }  /* String literal */
[a-zA-Z_][a-zA-Z0-9_]* { fprintf(yyout, "id");}
[ \t\n]+         { /* Ignore whitespace */ }

.                { fprintf(yyout, "UNKNOWN"); }  /* Catch-all for any other character */
%%

int main(int argc, char **argv) {
    yyin = fopen("code.txt", "r");
    if (!yyin) {
        perror("Unable to open code.txt");
        exit(1);
    }

    yyout = fopen("tokens.txt", "w");
    if (!yyout) {
        perror("Unable to open tokens.txt");
        exit(1);
    }

    yylex();

    fclose(yyin);
    fclose(yyout);

    return 0;
}

int yywrap() {
    return 1;
}
