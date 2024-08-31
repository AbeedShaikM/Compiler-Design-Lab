#include "PredictiveParser.hpp"

c_predictiveParser::c_predictiveParser(){

}

void c_predictiveParser::f_populateTable(char p_startSymbol){
  map<char, set<char>> l_first = f_getFirst();
  map<char, set<char>> l_follow = f_getFollow(p_startSymbol);

  for(char l_nonterminal: m_nonTerminals){
    for(string l_varString: m_productionRules[l_nonterminal]){
      if(l_varString == "epsilon"){
        for(char l_followTerminal: l_follow[l_nonterminal]){
          m_table[l_nonterminal][l_followTerminal] = "epsilon";
        }
        continue;
      }
      for(int i = 0; i <= (int)l_varString.size(); i++){
        if(i == (int)l_varString.size()){
          for(char l_followTerminal: l_follow[l_nonterminal]){
            m_table[l_nonterminal][l_followTerminal] = "epsilon";
          }
          continue;
        }
        char l_symbol = l_varString[i];
        if(m_terminals.find(l_symbol) != m_terminals.end()){
          if(m_table[l_nonterminal].find(l_symbol) != m_table[l_nonterminal].end()){
            cout << "Grammar is not LL(1)\n";
            assert(false);
          }
          m_table[l_nonterminal][l_symbol] = l_varString;
          break;
        }
        bool l_hasepsilon = false;
        for(char l_firstTerminal: l_first[l_symbol]){
          if(l_firstTerminal == '#'){
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

void c_predictiveParser::f_printParseTable(char p_startSymbol){
  f_populateTable(p_startSymbol);
  cout << "\n";
  for(char l_nonTerminal: m_nonTerminals){
    for(char l_terminal: m_terminals){
      cout << l_nonTerminal << "[" << l_terminal << "]\t=";
      if(m_table[l_nonTerminal].find(l_terminal) == m_table[l_nonTerminal].end()) cout << "\tError\n";
      else cout << "\t" << l_nonTerminal << "--->" << m_table[l_nonTerminal][l_terminal] << "\n";
    }
    cout << l_nonTerminal << "[$]\t=";
    if(m_table[l_nonTerminal].find('$') == m_table[l_nonTerminal].end()) cout << "\tError\n";
    else cout << "\t" << l_nonTerminal << "--->" << m_table[l_nonTerminal]['$'] << "\n";
    cout << "\n\n";
  }
}

bool c_predictiveParser::f_isAccepted(string p_inputString, char p_startSymbol){
  stack<char> l_stack;
  l_stack.push(p_startSymbol);
  p_inputString += '$';
  int l_pos = 0;
  while(not l_stack.empty()){
    char l_top = l_stack.top();
    l_stack.pop();
    if(m_terminals.find(l_top) != m_terminals.end()){
      if(p_inputString[l_pos] != l_top) return false; 
      l_pos++;
      continue;
    }
    if(m_table[l_top].find(p_inputString[l_pos]) == m_table[l_top].end()) return false;
    string l_applied = m_table[l_top][p_inputString[l_pos]];
    cout << l_top << "\t----->\t" << l_applied << "\n";
    if(l_applied == "epsilon"){
      continue;
    }
    for(int i = l_applied.size() - 1; i >= 0; i--){
      l_stack.push(l_applied[i]);
    }
  }

  return true;
}