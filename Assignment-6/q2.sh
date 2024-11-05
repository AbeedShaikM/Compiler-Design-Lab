flex lex2.l
yacc -d bison2.y
gcc lex.yy.c y.tab.c -lm -o q2
./q2 < input2.txt