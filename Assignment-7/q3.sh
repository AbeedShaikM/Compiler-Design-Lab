flex q3.l
yacc -d q3.y
gcc lex.yy.c y.tab.c -lm -o q3
./q3 < input3.txt