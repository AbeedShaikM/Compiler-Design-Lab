#include "PredictiveParser.hpp"

c_predictiveParser::c_predictiveParser(){

}

void c_predictiveParser::f_populateTable(string p_startSymbol){
  map<string, set<string>> l_first = f_getFirst();
  map<string, set<string>> l_follow = f_getFollow(p_startSymbol);
  
  for(string l_nonterminal: m_nonTerminals){
    for(string l_varString: m_productionRules[l_nonterminal]){
      if(l_varString == "epsilon"){
        for(string l_followTerminal: l_follow[l_nonterminal]){
          if(m_table[l_nonterminal].find(l_followTerminal) != m_table[l_nonterminal].end()){
            cout << "Grammar is not LL(1)\n";
            assert(false);
          }
          m_table[l_nonterminal][l_followTerminal] = "epsilon";
        }
        continue;
      }
      vector<string> l_symbols = f_getSymbols(l_varString);
      for(int i = 0; i <= (int)l_symbols.size(); i++){
        if(i == (int)l_varString.size()){
          for(string l_followTerminal: l_follow[l_nonterminal]){
            if(m_table[l_nonterminal].find(l_followTerminal) != m_table[l_nonterminal].end()){
              cout << "Grammar is not LL(1)\n";
              assert(false);
            }
            m_table[l_nonterminal][l_followTerminal] = "epsilon";
          }
          continue;
        }
        string l_symbol = l_symbols[i];
        if(m_terminals.find(l_symbol) != m_terminals.end()){
          if(m_table[l_nonterminal].find(l_symbol) != m_table[l_nonterminal].end()){
            cout << "Grammar is not LL(1)\n";
            assert(false);
          }
          m_table[l_nonterminal][l_symbol] = l_varString;
          break;
        }
        bool l_hasepsilon = false;
        for(string l_firstTerminal: l_first[l_symbol]){
          if(l_firstTerminal == "epsilon"){
            l_hasepsilon = true;
            continue;
          }
          if(m_table[l_nonterminal].find(l_firstTerminal) != m_table[l_nonterminal].end()){
            cout << "Grammar is not LL(1)\n";
            assert(false);
          }
          m_table[l_nonterminal][l_firstTerminal] = l_varString;
        }
        if(not l_hasepsilon) break;
      }
    }
  }
}

void c_predictiveParser::f_printParseTable(string p_startSymbol, string p_outputFileName){
  f_populateTable(p_startSymbol);
  ofstream l_outputFile(p_outputFileName);
  cout << "\n";
  for(string l_nonTerminal: m_nonTerminals){
    for(string l_terminal: m_terminals){
      l_outputFile << l_nonTerminal << "[" << l_terminal << "]\t=";
      if(m_table[l_nonTerminal].find(l_terminal) == m_table[l_nonTerminal].end()) l_outputFile << "\tError\n";
      else l_outputFile << "\t" << l_nonTerminal << "--->" << m_table[l_nonTerminal][l_terminal] << "\n";
    }
    l_outputFile << l_nonTerminal << "[$]\t=";
    if(m_table[l_nonTerminal].find("$") == m_table[l_nonTerminal].end()) l_outputFile << "\tError\n";
    else cout << "\t" << l_nonTerminal << "--->" << m_table[l_nonTerminal]["$"] << "\n";
    l_outputFile << "\n\n";
  }
  l_outputFile.close();
}

bool c_predictiveParser::f_isAccepted(string p_inputString, string p_startSymbol){
  vector<string> p_inputSymbols = f_getSymbols(p_inputString);
  stack<string> l_stack;
  l_stack.push(p_startSymbol);
  p_inputSymbols.push_back("$");
  int l_pos = 0;
  while(not l_stack.empty()){
    string l_top = l_stack.top();
    // cout << l_top << " " << p_inputSymbols[l_pos] << "\n";
    l_stack.pop();
    if(m_terminals.find(l_top) != m_terminals.end()){
      if(p_inputSymbols[l_pos] != l_top) return false; 
      l_pos++;
      continue;
    }
    if(m_table[l_top].find(p_inputSymbols[l_pos]) == m_table[l_top].end()) return false;
    string l_applied = m_table[l_top][p_inputSymbols[l_pos]];
    cout << l_top << "\t----->\t" << l_applied << "\n";
    if(l_applied == "epsilon"){
      continue;
    }
    vector<string> l_productionSymbols = f_getSymbols(l_applied);
    for(int i = l_productionSymbols.size() - 1; i >= 0; i--){
      l_stack.push(l_productionSymbols[i]);
    }
  }

  return l_pos == (int)p_inputSymbols.size() - 1;
}