# Recursive-Descent Parser and Grammar Transformation Tool

This repository contains a C++ implementation of various grammar transformation techniques (like left recursion removal, left factoring) and a recursive-descent parser. The implementation includes three functionalities:

1. **Left-Recursion Removal**
2. **Left-Factoring**
3. **Recursive-Descent Parsing**

## Contents
- `Grammar.hpp`: Header file defining the `c_grammar` class and its methods.
- `Grammar.cpp`: Implementation of methods for grammar transformations and parsing.
- `main.cpp`: Entry point to the program, handling user input and executing required functionalities.
- `Makefile`: Build script to compile the program.
- `README.md`: This file, explaining how to compile and run the program.
- `input<Q.No>_<EX.No>`: Contains input for Example - EX.No of question - Q.No.

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

The program expects the input in the following format:

1. **Number of Terminals**: Enter the number of terminal symbols.
2. **Terminals**: Enter the terminal symbols separated by spaces.
3. **Number of Non-terminals**: Enter the number of non-terminal symbols.
4. **Non-terminals and Production Rules**:
   - For each non-terminal:
     - Enter the non-terminal symbol.
     - Enter each production rule for the non-terminal.
     - After entering all production rules for that non-terminal, enter `!` to move to the next non-terminal.
5. **Functionality Choice**: After defining the grammar, choose one of the following options by entering the corresponding number:
   - `1`: Remove Left Recursion
   - `2`: Left Factor Grammar
   - `3`: Parse Input String Using Recursive-Descent Parser

## Troubleshooting

- Ensure that your grammar is provided correctly, and all rules are separated properly.
- When parsing, ensure the input string matches the given grammar rules.
- If you encounter issues with non-terminals or symbols being exhausted, check your inputs to ensure no overlaps or errors in your grammar.

This README provides the necessary details to use the program effectively. If you have any questions or face any issues, feel free to reach out.

