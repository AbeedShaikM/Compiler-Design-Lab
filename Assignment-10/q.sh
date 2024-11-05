flex q.l
yacc -d q.y
gcc lex.yy.c y.tab.c -lm -o q
./q < input.txt