flex q2.l
yacc -d q2.y
gcc lex.yy.c y.tab.c -lm -o q2
./q2 < input2.txt