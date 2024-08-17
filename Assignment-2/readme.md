# Lexical Analyzer Programs

## Section 1

### Q 1.1 Recognizes binary strings containing at least six 1’s

This program identifies binary strings that contain at least six `1`s.

### Q 1.2 Recognizes strings starting with “c” and ending with “r”

This program identifies strings that start with the letter `c` and end with the letter `r`, containing only letters and digits.

### Q 1.3 Recognizes strings over the alphabet {a, b, c} with length 6

This program identifies strings of length 6 over the alphabet {a, b, c} that contain either two consecutive `a`s or two consecutive `b`s.

## Section 2

### Q 2.1 Identifies Integers, Float Numbers, Character Constants, and String Constants

This program identifies integers, floating-point numbers, character constants, and string constants, ignoring any illegal or unexpected symbols.

## Section 3

### Lexical Analyzer for a Simple “C” Like Language

This program constructs a lexical analyzer for a simple "C" like language using the Lex/Flex tool. It recognizes data types, condition constructs, loop constructs, input/output constructs, relational operators, assignment and arithmetic operators, and the main function.

## Compiling and Running

1. Save the code to a file, e.g., `lexer.l`.
2. Generate the lexical analyzer using `flex`:
   flex lexer.l
3. Compile the generated C file with a C compiler:
   gcc lex.yy.c -o lexer
4. Run the resulting executable:
   ./lexer (if required)