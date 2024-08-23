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

  o_grammar.f_print();
  int q;
  cin >> q;

  switch (q){
    case 1:{
      map<char, set<char>> l_result = o_grammar.f_getFirst();
      for(auto [l_nonTerminal, l_first]: l_result){
        cout << "First (" << l_nonTerminal << ")\t => {";
        for(char l_terminal: l_first){
          if(l_terminal == '#'){
            cout << " epsilon,";
            continue;
          }
          cout << " " << l_terminal << ",";
        }
        cout << "}\n";
      }
      break;
    }
    case 2:{
      char l_startSymbol;
      cin >> l_startSymbol;
      map<char, set<char>> l_result = o_grammar.f_getFollow(l_startSymbol);
      for(auto [l_nonTerminal, l_first]: l_result){
        cout << "Follow (" << l_nonTerminal << ")\t => {";
        for(char l_terminal: l_first){
          if(l_terminal == '#'){
            cout << " epsilon,";
            continue;
          }
          cout << " " << l_terminal << ",";
        }
        cout << "}\n";
      }
      break;
    }
    default:
      cout << "Incorrect question number\n";
  }
  
  return 0;
}