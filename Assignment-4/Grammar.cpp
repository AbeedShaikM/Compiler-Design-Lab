#include "Grammar.hpp"

c_grammar::c_grammar(){
  m_trie.resize(1, map<char, int>{});
  m_isEnd.resize(1);
}

void c_grammar::f_addString(string p_symbol){
  int l_start = 0;
  for(char l_char: p_symbol){
    // cout << l_char << " ";
    if(m_trie[l_start].find(l_char) == m_trie[l_start].end()) m_trie[l_start][l_char] = m_trie.size(), m_trie.push_back(map<char, int>{}), m_isEnd.push_back(0);
    l_start = m_trie[l_start][l_char];
  }
  if(m_isEnd[l_start]){
    cout << p_symbol << " is used twice\n";
    assert(false);
  }
  // cout << "\n";
  m_isEnd[l_start] = 1;
}

void c_grammar::f_addTerminal(string p_terminal){
  f_addString(p_terminal);
  m_terminals.insert(p_terminal);
}

void c_grammar::f_addNonTerminal(string p_nonTerminal){
  f_addString(p_nonTerminal);
  m_nonTerminals.insert(p_nonTerminal);
}

void c_grammar::f_removeProductionRule(string p_nonTerminal, string p_varString){
  m_productionRules[p_nonTerminal].erase(p_varString);
}

void c_grammar::f_addProductionRule(string p_nonTerminal, string p_varString){
  m_productionRules[p_nonTerminal].insert(p_varString);
}

void c_grammar::f_print(){
  for(auto [l_nonTerminal, l_varStrings]: m_productionRules){
    cout << l_nonTerminal << "\t--->";
    for(auto l_varString: l_varStrings){
      cout << "\t";
      cout << l_varString;
    }
    cout << "\n";
  }
}

string c_grammar::f_getNewSymbol(string p_symbol){
  string l_newSymbol = p_symbol + '\'';
  return l_newSymbol;
}

vector<string>c_grammar::f_getSymbols(string p_productionRule){
  int l_left = 0, l_right = 0, l_start = 0;
  string l_currSymbol = "";
  vector<string> l_result;
  if(p_productionRule == "epsilon"){
    l_result.push_back("epsilon");
    return l_result;
  }
  while(l_right < (int)p_productionRule.size()){
    if(m_trie[l_start].find(p_productionRule[l_right]) == m_trie[l_start].end()){
      if(l_currSymbol == ""){
        for(int i = 0; i < l_result.size(); i++) cout << l_result[i] << " ";
        cout << "\n";
        cout << l_currSymbol << " " << l_right << " " << p_productionRule << "\n";
        cout << "String contains incorrect symbols\n";
        assert(false);
      }
      l_right = l_left;
      l_result.push_back(l_currSymbol);
      l_start = 0;
      l_currSymbol = "";
      continue;
    }
    l_start = m_trie[l_start][p_productionRule[l_right]];
    if(m_isEnd[l_start]) l_currSymbol += p_productionRule.substr(l_left, l_right - l_left + 1), l_left = l_right + 1;
    l_right++;
  }
  if(l_left == l_right) l_result.push_back(l_currSymbol);
  else{
    cout << "String contains incorrect symbols\n";
    assert(false);
  }
  return l_result;
}

bool c_grammar::f_hasImmediateRecursion(string p_nonTerminal){
  for(string l_varString: m_productionRules[p_nonTerminal]){
    vector<string> l_symbols = f_getSymbols(l_varString);
    if(l_symbols[0] == p_nonTerminal) return true;
  }
  return false;
}

bool c_grammar::f_hasImmediateRecursion(string p_nonTerminal){
  for(string l_varString: m_productionRules[p_nonTerminal]){
    vector<string> l_symbols = f_getSymbols(l_varString);
    if(l_symbols[0] == p_nonTerminal) return true;
  }
  return false;
}

bool c_grammar::f_removeImmediateLeftRecursion(string p_nonTerminal){
  if(f_hasImmediateRecursion(p_nonTerminal)){
    string l_newSymbol = f_getNewSymbol(p_nonTerminal);
    f_addNonTerminal(l_newSymbol);
    set<string> l_productionRule = m_productionRules[p_nonTerminal];
    for(string l_varString: l_productionRule){
      vector<string> l_symbols = f_getSymbols(l_varString);
      if(l_symbols[0] == p_nonTerminal){
        f_addProductionRule(l_newSymbol, l_varString.substr((int)l_symbols[0].size()) + l_newSymbol);
      }
      else{
        f_addProductionRule(p_nonTerminal, (l_varString == "epsilon" ? "" : l_varString) + l_newSymbol);
      }
      m_productionRules[p_nonTerminal].erase(l_varString);
    }
    f_addProductionRule(l_newSymbol, "epsilon");
    return true;
  }
  return false;
}

void c_grammar::f_removeLeftRecursion(){
  assert(m_nonTerminals.size() == m_productionRules.size());
  set<string> l_nonTerminals = m_nonTerminals; 
  for(string l_nonTerminal: l_nonTerminals){
    set<string> l_tempProd = m_productionRules[l_nonTerminal];
    for(string l_nonTerminal_: m_nonTerminals){
      set<string> l_newProductionRule = m_productionRules[l_nonTerminal];
      if(l_nonTerminal == l_nonTerminal_) break;
      for(string l_varString: m_productionRules[l_nonTerminal]){
        vector<string> l_symbols = f_getSymbols(l_varString);
        if(l_symbols[0] == l_nonTerminal_){
          for(string l_varString_: m_productionRules[l_nonTerminal_]){
            l_newProductionRule.insert((l_varString_ == "epsilon" ? "": l_varString_) + l_varString.substr((int)l_symbols[0].size()));
          }
          l_newProductionRule.erase(l_varString);
        }
      }
      m_productionRules[l_nonTerminal] = l_newProductionRule;
    }
    if(f_removeImmediateLeftRecursion(l_nonTerminal));
    else m_productionRules[l_nonTerminal] = l_tempProd;
  }
}

void c_grammar::f_leftFactor(){
  stack<string> l_st;
  for(string c: m_nonTerminals) l_st.push(c);
  while(not l_st.empty()){
    string l_nonTerminal = l_st.top();
    l_st.pop();
    vector<map<string, int>> l_trie(1);
    vector<int> l_size(1, 0);
    vector<string> l_ends(1);
    for(string l_varString: m_productionRules[l_nonTerminal]){
      if(l_varString == "epsilon") continue;
      vector<string> l_symbols = f_getSymbols(l_varString); 
      int l_start = 0;
      for(string l_symbol: l_symbols){
        l_size[l_start]++;
        if(l_trie[l_start].find(l_symbol) == l_trie[l_start].end()){
          l_trie[l_start][l_symbol] = l_trie.size();
          l_trie.push_back({});
          l_ends.push_back("");
          l_size.push_back(0);
        }
        l_start = l_trie[l_start][l_symbol];
      }
      l_ends[l_start] = l_varString;
      l_size[l_start]++;
    }

    for(auto [l_symbol, l_next]: l_trie[0]){
        if(l_size[l_next] < 2) continue;
        int sz = l_symbol.size();
        while(l_trie[l_next].size() == 1) {
          int l_nextPoss = l_trie[l_next].begin()->second;
          if(l_size[l_nextPoss] == l_size[l_next]) sz += l_trie[l_next].begin()->first.size(), l_next = l_nextPoss;
          else break;
        }
        vector<string> l_commonPrefixes = f_getStringsWithSamePrefix(l_next, l_trie, l_ends);
        string l_notUsedSymbol = f_getNewSymbol(l_nonTerminal);
        f_addNonTerminal(l_notUsedSymbol);
        for(string l_varString: l_commonPrefixes){
          f_removeProductionRule(l_nonTerminal, l_varString);
          if((int)l_varString.size() != sz) f_addProductionRule(l_notUsedSymbol, l_varString.substr(sz));
          else f_addProductionRule(l_notUsedSymbol, "epsilon");
        }
        f_addProductionRule(l_nonTerminal, l_commonPrefixes[0].substr(0, sz) + l_notUsedSymbol);
        if((int)l_commonPrefixes[0].size() == sz) f_addProductionRule(l_notUsedSymbol, "epsilon");
        l_st.push(l_notUsedSymbol);
    }
  }
}

vector<string> c_grammar::f_getStringsWithSamePrefix(int root, vector<map<string, int>>& p_trie, vector<string>& p_ends){
  vector<string> l_result;
  if(p_ends[root] != "") l_result.push_back(p_ends[root]);
  for(auto [l_symbol, l_next]: p_trie[root]){
    vector<string> l_subResult = f_getStringsWithSamePrefix(l_next, p_trie, p_ends);
    l_result.insert(l_result.end(), l_subResult.begin(), l_subResult.end());
  }

  return l_result;
}

bool c_grammar::f_getParseTree(string& p_grammarString, string p_startSymbol){
  stack<string> l_sententialForm;
  l_sententialForm.push(p_startSymbol);
  vector<string> l_symbols = f_getSymbols(p_grammarString);
  return f_isAccepted(l_symbols, l_sententialForm, 0);
}

bool c_grammar::f_isAccepted(vector<string> p_grammarString, stack<string> p_sententialForm, int p_pos){
  if(p_sententialForm.empty() and p_pos == (int)p_grammarString.size()) return true;
  if(p_sententialForm.empty()) return false;
  string curr = p_sententialForm.top();
  p_sententialForm.pop();
  if(m_nonTerminals.find(curr) != m_nonTerminals.end()){
    bool flag = false;
    for(string l_varString: m_productionRules[curr]){
      cout << "Taking " << curr << "\t---->\t" << l_varString << "\n";
      stack<string> temp_st = p_sententialForm;
      if(l_varString != "epsilon") {
        vector<string> l_symbols = f_getSymbols(l_varString);
        for(int i = l_symbols.size() - 1; i >= 0; i--) temp_st.push(l_symbols[i]);
      }
      if(f_isAccepted(p_grammarString, temp_st, p_pos)) {
        flag = true;
        break;
      }
      cout << "Backtracking: " << curr << "\t---->\t" << l_varString << "\n";
    }
    return flag;
  }
  else{
    if((int)p_grammarString.size() == p_pos) return false;
    if(p_grammarString[p_pos] == curr){
      return f_isAccepted(p_grammarString, p_sententialForm, p_pos + 1);
    }
    else return false;
  }
}

map<string, set<string>> c_grammar::f_getFirst(){
  map<string, set<string>> l_result;
  while(true){
    bool l_change = false;
    for(string l_nonTerminal: m_nonTerminals){
      for(string l_varString: m_productionRules[l_nonTerminal]){
        if(l_varString == "epsilon"){
          if(l_result[l_nonTerminal].find("epsilon") == l_result[l_nonTerminal].end()){
            l_result[l_nonTerminal].insert("epsilon");
            l_change = true;
          }
          continue;
        }
        vector<string> l_symbols = f_getSymbols(l_varString);
        for(int i = 0; i <= (int)l_symbols.size(); i++){
          if(i == (int)l_symbols.size()){
            if(l_result[l_nonTerminal].find("epsilon") == l_result[l_nonTerminal].end()){
              l_result[l_nonTerminal].insert("epsilon");
              l_change = true;
            }
            continue;
          }
          string l_symbol = l_symbols[i];
          if(m_terminals.find(l_symbol) != m_terminals.end()){
            if(l_result[l_nonTerminal].find(l_symbol) == l_result[l_nonTerminal].end()){
              l_change = true;
              l_result[l_nonTerminal].insert(l_symbol);
            }
            break;
          }
          bool l_hasEpsilon = false;
          for(string l_first: l_result[l_symbol]){
            if(l_first == "epsilon"){
              l_hasEpsilon = true;
              continue;
            } 
            if(l_result[l_nonTerminal].find(l_first) == l_result[l_nonTerminal].end()){
              l_result[l_nonTerminal].insert(l_first);
              l_change = true;
            }
          }
          if(not l_hasEpsilon) break;
        }
      }
    }
    if(l_change) continue;
    break;
  }

  return l_result;
}

map<string, set<string>>c_grammar::f_getFollow(string p_startSymbol){
  map<string, set<string>> l_result;
  map<string, set<string>> l_first = f_getFirst();
  l_result[p_startSymbol].insert("$");
  while(true){
    bool l_change = false;
    for(string l_nonTerminal: m_nonTerminals){
      for(string l_varString: m_productionRules[l_nonTerminal]){
        if(l_varString == "epsilon") continue;
        vector<string> l_symbols = f_getSymbols(l_varString);
        for(int i = 0; i < (int)l_symbols.size(); i++){
          if(m_terminals.find(l_symbols[i]) != m_terminals.end()){
            continue;
          }
          for(int j = i + 1; j <= (int)l_symbols.size(); j++){
            if(j == (int)l_symbols.size()){
              for(string l_symbol: l_result[l_nonTerminal]){
                if(l_result[l_symbols[i]].find(l_symbol) == l_result[l_symbols[i]].end()){
                  l_change = true;
                  l_result[l_symbols[i]].insert(l_symbol);
                }
              }
              continue;
            }
            if(m_terminals.find(l_symbols[j]) != m_terminals.end()){
              if(l_result[l_symbols[i]].find(l_symbols[j]) == l_result[l_symbols[i]].end()){
                l_change = true;
                l_result[l_symbols[i]].insert(l_symbols[j]);
              }
              break;
            }
            bool l_hasEpsilon = false;
            for(string l_symbol: l_first[l_symbols[j]]){
              if(l_symbol == "epsilon") {
                l_hasEpsilon = true;
                continue;
              }
              if(l_result[l_symbols[i]].find(l_symbol) == l_result[l_symbols[i]].end()){
                l_change = true;
                l_result[l_symbols[i]].insert(l_symbol);
              }
            }
            if(not l_hasEpsilon) break;
          }
        }
      }
    }
    if(l_change) continue;
    break;
  }

  return l_result;
}