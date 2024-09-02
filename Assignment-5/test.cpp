#include "PredictiveParser.hpp"

int main(){
  c_predictiveParser o_predictiveParser;
  int l_terminalCount, l_nonTerminalCount;
  // cout << "Enter no. of terminals: ";
  cin >> l_terminalCount;
  // cout << "Enter no. of non-terminals: ";
  cin >> l_nonTerminalCount;

  // cout << "Enter terminals: ";
  for(int i = 0; i < l_terminalCount; i++){
    string l_terminal;
    cin >> l_terminal;
    o_predictiveParser.f_addTerminal(l_terminal);
  }
  
  // cout << "Enter non-terminals (upper case letters): ";
  for(int i = 0; i < l_nonTerminalCount; i++){
    string l_nonTerminal;
    cin >> l_nonTerminal;
    o_predictiveParser.f_addNonTerminal(l_nonTerminal);

    // cout << "Enter production rule for non-terminal " << l_nonTerminal << " (Enter '!' for exit): ";
    while(true){
      string s;
      cin >> s;
      if(s == "!") break;
      o_predictiveParser.f_addProductionRule(l_nonTerminal, s);
    }
  }

  o_predictiveParser.f_print();
  o_predictiveParser.f_removeLeftRecursion();
  o_predictiveParser.f_leftFactor();
  cout << "\n";
  o_predictiveParser.f_print();
  string l_startSymbol;
  cin >> l_startSymbol;
  o_predictiveParser.f_printParseTable(l_startSymbol, "parseTable.txt");
  string l_inputString;
  ifstream inputFile("tokens.txt");
  inputFile >> l_inputString;
  if(o_predictiveParser.f_isAccepted(l_inputString, l_startSymbol)){
    cout << "Input string is accepted by the grammar\n";
  }
  else cout << "Input string is not accepted by the grammar\n";
}