#include "Grammar.hpp"

int main(){
  c_grammar o_grammar;
  int l_terminalCount, l_nonTerminalCount;
  // cout << "Enter no. of terminals: ";
  cin >> l_terminalCount;
  // cout << "Enter no. of non-terminals: ";
  cin >> l_nonTerminalCount;

  // cout << "Enter terminals: ";
  for(int i = 0; i < l_terminalCount; i++){
    string l_terminal;
    cin >> l_terminal;
    o_grammar.f_addTerminal(l_terminal);
  }

  // cout << "Enter non-terminals (upper case letters): ";
  for(int i = 0; i < l_nonTerminalCount; i++){
    string l_nonTerminal;
    cin >> l_nonTerminal;
    o_grammar.f_addNonTerminal(l_nonTerminal);

    // cout << "Enter production rule for non-terminal " << l_nonTerminal << " (Enter '!' for exit): ";
    while(true){
      string s;
      cin >> s;
      if(s == "!") break;
      o_grammar.f_addProductionRule(l_nonTerminal, s);
    }
  }

  int q_no;
  cin >> q_no;
  o_grammar.f_print();

  switch (q_no){
  case 1:
    // o_grammar.f_leftFactor();
    o_grammar.f_removeLeftRecursion();
    cout << "\nGrammar after removing left recursion.\n";
    o_grammar.f_print();
    break;
  case 2:
    o_grammar.f_leftFactor();
    cout << "\nGrammar after left factoring.\n";
    o_grammar.f_print();
    break;
  case 3:{
    string s;
    cin >> s;
    string c;
    cin >> c;
    o_grammar.f_removeLeftRecursion();
    cout << "\nGrammar after removing left recursion.\n";
    o_grammar.f_print();
    cout << "\n";
    if(not o_grammar.f_getParseTree(s, c)) cout << "\n" << s << " is not accepted by the given grammar.\n";
    else cout << "\n" << s << " is accepted by the given grammar.\n";
    break;
  }
  default:
    cout << "Invalid question number\n";
  }

  return 0;
}