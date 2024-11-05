# Lexical Analyzers and Parsers Assignment

## Overview

This assignment involves building lexical analyzers and parsers using Lex/Flex and Yacc/Bison tools. The provided example grammars will guide the construction of the lexical analyzer and parser. This README file contains details on how to compile and generate code from the specifications, as well as how to run and test the code.

## Example Grammars

### Grammar 1

**Non-terminals:** {E, T, F}  
**Start symbol:** E  
**Terminal symbols:** { id, (, ), +, \* }

### Grammar 2

**Non-terminals:**  
{ AE, BE, D, DL, E, F, ES, IOS, IS, NE, P, PE, RE, S, SL, T, TY, VL, WS }

**Terminals:**  
{ +, −, ∗, /, =, <, >, (, ), {, }, :=, ;, and, else, end, ic, id, if, int, do, fc, float, not, or, print, prog, scan, str, then, while }

**Start symbol:** P

## Files and Specifications

1. **Lex/Flex File**: `lexer.l`
2. **Yacc/Bison File**: `grammar.y`

## How to Compile and Generate Code

```bash
    flex lexer.lex
    yacc -d grammar.y
    gcc y.tab.c lex.yy.c -o parser
```

## How to Execute

1. **Run the Lexer**:

   ```bash
   ./parser < input_file
   ```

   This command processes the `input_file` through the lexer and outputs tokens.

2. **Run the Parser**:

   ```bash
   ./parser < input_file
   ```

   This command processes the `input_file` through the parser and outputs the result based on the defined grammar.

## Sample Test Inputs

**Input File 1** (for Grammar 1):

```text
id + ( id * id )
```

**Input File 2** (for Grammar 2):

```text
prog
if 3 < 4 then
  print "Abeed"
else
  print "Priyam"
end
end
```

## Notes

- Ensure that Lex/Flex and Yacc/Bison are installed on your system before running the commands.
- Modify `lexer.l` and `parser.y` according to the specifications of the provided grammars.
- The generated executables (`lexer` and `parser`) should be run with an appropriate input file to test the lexical analyzer and parser functionalities.

## Submission

- Submit the `lexer.l` and `parser.y` files.
- Include this README file with instructions on how to compile, generate, and execute the code.
- Provide sample test inputs and any other relevant details.
