flex q.l
yacc -d q.y
g++ lex.yy.c y.tab.c ast.cpp -I/usr/include/graphviz -L/usr/lib/graphviz -lgvc -lcgraph -o prog1
./prog1 < input.txt
