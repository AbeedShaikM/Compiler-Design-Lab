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
    char l_terminal;
    cin >> l_terminal;
    o_grammar.f_addTerminal(l_terminal);
  }

  // cout << "Enter non-terminals (upper case letters): ";
  for(int i = 0; i < l_nonTerminalCount; i++){
    char l_nonTerminal;
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
    char c;
    cin >> c;
    o_grammar.f_removeLeftRecursion();
    cout << "\nGrammar after removing left recursion.\n";
    o_grammar.f_print();
    cout << "\n";
    int id = 1;
    int l_result = o_grammar.f_getParseTree(s, 'G', true, id, 1);
    cout << "\n";
    if(l_result == -1) cout << s << " is not accepted by the given grammar.\n";
    else cout << s << " is accepted by the given grammar.\n";
    break;
  }
  default:
    cout << "Invalid question number\n";
  }

  return 0;
}