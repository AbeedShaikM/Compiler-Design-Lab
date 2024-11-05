Commands to run the codes:

1. Go to the respective directory containing the lex and yacc files.
2. Run the following commands:
    flex <file_name>.l
    yacc -d <file_name>.y
    gcc y.tab.c lex.yy.c -o parser -lm
    ./parser

3. Sample input for Q2:
    4 - 3 * 5 =

    desired output: -11

4. Sample input for Q3:
    log10(sqrt(2)) =

    desired output: 0.150515

NOTE: Every input must end with an "equal to" ("=") sign.
