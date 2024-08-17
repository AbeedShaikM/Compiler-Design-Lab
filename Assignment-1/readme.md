# Lexical Analyzer for Simple Algebraic Expressions

This program is a lexical analyzer that processes a simple algebraic expression and outputs the corresponding sequence of tokens.

## Grammar Rules

The program tokenizes the input based on the following grammar rules:

- **Identifiers**: letter.(letter+digit)*
- **Constants**: digit.digit*
- **Operators**: {+, -, *, /}
- **Parentheses**: “(”, “)”

## Output Format
- <token_type, token_value>

## Example

### Input
- temp1+25*(bal2-53)

### Ouput
- (id, temp1)
- (+, opr)
- (const, 25)
- (*, opr)
- ( (, )
- (id, bal2)
- (-, opr)
- (const, 53)
- ( ), )

