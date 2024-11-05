flex q2.l
yacc -d q2.y
g++ lex.yy.c y.tab.c DAG.cpp -I/usr/include/graphviz -L/usr/lib/graphviz -lgvc -lcgraph -o prog2
./prog2 < input.txt