%{
#include <stdio.h>
%}

%%

(int|INT)             	{ printf("<DataType, Integer> \n"); }
(float|FLOAT)         	{ printf("<DataType, Float> \n"); }
(char|CHAR)           	{ printf("<DataType, Char> \n"); }
(bool|Bool)           	{ printf("<DataType, Boolean> \n"); }
input                  	{ printf("<Keyword, input> \n"); }
read                   	{ printf("<Keyword, read>\n" ); }
out                    	{ printf("<Keyword, out> \n"); }
if                    	{ printf("<ConditionalOp, if> \n"); }
(for|while)           	{ printf("<LoopOp, %s> \n", yytext); }
read\(.*\)            	{ printf("<Input, %s> \n", yytext); }
out\(.*\)             	{ printf("<Output, %s> \n", yytext); }
(==|!=|<=|>=|<|>)     	{ printf("<RelationalOp, %s> \n", yytext); }
=                     	{ printf("<AssignmentOp, => \n"); }
(\+|\-|\*|\/)         	{ printf("<ArithmeticOp, %s> \n", yytext); }
[-]?[0-9]+            	{ printf("<IntegerConst, %s> \n", yytext); }
[-]?[0-9]+\.[0-9]+    	{ printf("<FloatConst, %s> \n", yytext); }
'[^']'                	{ printf("<CharacterConst, %s> \n", yytext); }
\"[^\"]*\"            	{ printf("<StringConst, %s> \n", yytext); }
main                  	{ printf("<Function, main> \n"); }
\(|\)           		{ printf("<Parentheses, %s> \n", yytext); }
\{|\}					{ printf("<Braces, %s> \n", yytext); }
[a-zA-Z_][a-zA-Z_0-9]* 	{ printf("<Identifier, %s> \n", yytext); }
;						{ printf("<Semicolon, ;>\n"); }
[ \t\n\r]+            	{;}
.                     	{ printf("<Illegal, %s> \n", yytext); }

%%

int yywrap(void){
  return 1;
}

int main(int argc, char **argv)
{
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            fprintf(stderr, "Usage %s <FileName>\n", argv[0]);
            return 1;
        }
        yyin = file;
    }

	printf("<Type, Token> pairs:\n"); 
    yylex();
    printf("\n");

    return 0;
}