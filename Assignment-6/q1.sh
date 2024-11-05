flex lex1.l
yacc -d bison1.y
gcc lex.yy.c y.tab.c -lm -o q1
./q1 < input1.txt