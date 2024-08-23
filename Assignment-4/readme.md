# Assignment: FIRST() and FOLLOW() Sets Computation for Context-Free Grammars

## Objective

The objective of this assignment is to implement a program or function to compute the `FIRST()` and `FOLLOW()` sets for any given context-free grammar (CFG). These functions are crucial for constructing parsers and understanding the structure of a CFG.

## Tasks

### (Q1) Implement a Program/Function for Computing FIRST() Sets

- Implement a function to compute the `FIRST()` sets for all non-terminals in a given CFG.
- The `FIRST()` set for a non-terminal is the set of terminal symbols that begin the strings derivable from that non-terminal.

### (Q2) Implement a Program/Function for Computing FOLLOW() Sets

- Implement a function to compute the `FOLLOW()` sets for all non-terminals in a given CFG.
- The `FOLLOW()` set for a non-terminal is the set of terminal symbols that can appear immediately to the right of that non-terminal in some "sentential" form.

## How to Build the Program

1. **Ensure you have a C++20 compliant compiler installed.**
   - You can use `g++`, for example.
   
2. **Compile the Program:**
   - Navigate to the directory containing the source files.
   - Run the following command to build the program:
     ```
     make
     ```
   - This will generate an executable named `main`.

3. **Clean the Build:**
   - If you wish to clean the build directory, use:
     ```
     make clean
     ```

## How to Use the Program
   - Run the execuatable created `./main`.

## Input Format

The program should take input in the following format:

1. **Number of Terminals**: The program first asks for the number of terminals.
2. **Number of Non-Terminals**: The program then asks for the number of non-terminals.
3. **Terminal Symbols**: Enter the terminal symbols one by one.
4. **Non-Terminal Symbols**: Enter the non-terminal symbols one by one.
5. **Production Rules**: For each non-terminal, you need to enter its production rules. Use the `!` symbol to indicate the end of the production rules for a non-terminal.
6. **Question Number**: The program then asks for the question number (1 for `FIRST()` sets, 2 for `FOLLOW()` sets).
7. **Start Symbol for FOLLOW() (Optional)**: If the user selects question 2 (FOLLOW sets), they should provide the start symbol.

## Example Input

```plaintext
3
3
n + ×
S B A
nB
!
nBAB
epsilon
!
+ ×
!
1

```

## Troubleshooting

- Ensure that your grammar is provided correctly, and all rules are separated properly.
- When parsing, ensure the input string matches the given grammar rules.
- If you encounter issues with non-terminals or symbols being exhausted, check your inputs to ensure no overlaps or errors in your grammar.

This README provides the necessary details to use the program effectively. If you have any questions or face any issues, feel free to reach out.