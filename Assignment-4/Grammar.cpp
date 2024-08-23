#include "Grammar.hpp"

void c_grammar::f_addTerminal(char p_terminal){
  m_terminals.insert(p_terminal);
}

void c_grammar::f_addNonTerminal(char p_nonTerminal){
  m_nonTerminals.insert(p_nonTerminal);
}

void c_grammar::f_removeProductionRule(char p_nonTerminal, string p_varString){
  m_productionRules[p_nonTerminal].erase(p_varString);
}

void c_grammar::f_addProductionRule(char p_nonTerminal, string p_varString){
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

char c_grammar::f_getNotUsedSymbol(){
  for(int i = 0; i < 26; i++){
    if(m_nonTerminals.find('A' + i) == m_nonTerminals.end()) return 'A' + i;
  }
  cerr << "All symbols used\n";
  assert(false);
}

bool c_grammar::f_hasImmediateRecursion(char p_nonTerminal){
  for(auto l_varString: m_productionRules[p_nonTerminal]){
    if(l_varString[0] == p_nonTerminal) return true;
  }
  return false;
}

void c_grammar::f_removeImmediateLeftRecursion(char p_nonTerminal){
  if(f_hasImmediateRecursion(p_nonTerminal)){
    char l_nonTerminal = f_getNotUsedSymbol();
    f_addNonTerminal(l_nonTerminal);
    set<string> l_productionRule = m_productionRules[p_nonTerminal];
    for(string l_varString: l_productionRule){
      if(l_varString[0] == p_nonTerminal){
        f_addProductionRule(l_nonTerminal, l_varString.substr(1) + l_nonTerminal);
      }
      else{
        f_addProductionRule(p_nonTerminal, (l_varString == "epsilon" ? "" : l_varString) + l_nonTerminal);
      }
      m_productionRules[p_nonTerminal].erase(l_varString);
    }
    f_addProductionRule(l_nonTerminal, "epsilon");
  }
}

void c_grammar::f_removeLeftRecursion(){
  assert(m_nonTerminals.size() == m_productionRules.size());
  set<char> l_nonTerminals = m_nonTerminals; 
  for(char l_nonTerminal: l_nonTerminals){
    set<string> l_newProductionRule = m_productionRules[l_nonTerminal];
    for(char l_nonTerminal_: m_nonTerminals){
      if(l_nonTerminal == l_nonTerminal_) break;
      for(auto l_varString: m_productionRules[l_nonTerminal]){
        bool flag = false;
        if(l_varString[0] == l_nonTerminal_){
          for(auto l_varString_: m_productionRules[l_nonTerminal_]){
            if(l_varString_[0] == l_nonTerminal) flag = true;
          }
        }
        if(flag){
          for(auto l_varString_: m_productionRules[l_nonTerminal_]){
            l_newProductionRule.insert(l_varString.substr(1) + (l_varString_ == "epsilon" ? "": l_varString_));
          }
          l_newProductionRule.erase(l_varString);
        }
      }
    }
    for(string l_varString: l_newProductionRule){
      f_addProductionRule(l_nonTerminal, l_varString);
    }
    f_removeImmediateLeftRecursion(l_nonTerminal);
  }
}

void c_grammar::f_leftFactor(){
  stack<char> l_st;
  for(char c: m_nonTerminals) l_st.push(c);
  while(not l_st.empty()){
    char l_nonTerminal = l_st.top();
    l_st.pop();
    vector<map<char, int>> l_trie(1);
    vector<int> l_size(1, 0);
    vector<string> l_ends(1);
    for(string l_varString: m_productionRules[l_nonTerminal]){
      if(l_varString == "epsilon") continue;
      int l_start = 0;
      for(char l_symbol: l_varString){
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
        int sz = 1;
        if(l_size[l_next] < 2) continue;
        while(l_trie[l_next].size() == 1) {
          int l_nextPoss = l_trie[l_next].begin()->second;
          if(l_size[l_nextPoss] == l_size[l_next]) l_next =l_nextPoss;
          else break;
          sz++;
        }
        vector<string> l_commonPrefixes = f_getStringsWithSamePrefix(l_next, l_trie, l_ends);
        char l_notUsedSymbol = f_getNotUsedSymbol();
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

vector<string> c_grammar::f_getStringsWithSamePrefix(int root, vector<map<char, int>>& p_trie, vector<string>& p_ends){
  vector<string> l_result;
  if(p_ends[root] != "") l_result.push_back(p_ends[root]);
  for(auto [l_symbol, l_next]: p_trie[root]){
    vector<string> l_subResult = f_getStringsWithSamePrefix(l_next, p_trie, p_ends);
    l_result.insert(l_result.end(), l_subResult.begin(), l_subResult.end());
  }

  return l_result;
}

bool c_grammar::f_getParseTree(string& p_grammarString, char p_startSymbol){
  stack<char> l_sententialForm;
  l_sententialForm.push(p_startSymbol);
  return f_isAccepted(p_grammarString, l_sententialForm, 0);
}

bool c_grammar::f_isAccepted(string p_grammarString, stack<char> p_sententialForm, int p_pos){
  if(p_sententialForm.empty() and p_pos == (int)p_grammarString.size()) return true;
  if(p_sententialForm.empty()) return false;
  char curr = p_sententialForm.top();
  p_sententialForm.pop();
  if(m_nonTerminals.find(curr) != m_nonTerminals.end()){
    bool flag = false;
    for(string l_varString: m_productionRules[curr]){
      cout << "Taking " << curr << "\t---->\t" << l_varString << "\n";
      stack<char> temp_st = p_sententialForm;
      if(l_varString != "epsilon") {
        for(int i = l_varString.size() - 1; i >= 0; i--) temp_st.push(l_varString[i]);
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

map<char, set<char>> c_grammar::f_getFirst(){
  map<char, set<char>> l_result;
  while(true){
    bool l_change = false;
    for(char l_nonTerminal: m_nonTerminals){
      for(string l_varString: m_productionRules[l_nonTerminal]){
        if(l_varString == "epsilon"){
          l_result[l_nonTerminal].insert('#');
          continue;
        }
        for(char l_symbol: l_varString){
          if(m_terminals.find(l_symbol) != m_terminals.end()){
            if(l_result[l_nonTerminal].find(l_symbol) == l_result[l_nonTerminal].end()){
              l_change = true;
              l_result[l_nonTerminal].insert(l_symbol);
            }
            break;
          }
          bool l_hasEpsilon = false;
          for(char l_first: l_result[l_symbol]){
            if(l_result[l_nonTerminal].find(l_first) == l_result[l_nonTerminal].end()){
              l_result[l_nonTerminal].insert(l_first);
              l_change = true;
            }
            if(l_first == '#') l_hasEpsilon = true;
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

map<char, set<char>>c_grammar::f_getFollow(char p_startSymbol){
  map<char, set<char>> l_result;
  map<char, set<char>> l_first = f_getFirst();
  l_result[p_startSymbol].insert('$');
  while(true){
    bool l_change = false;
    for(char l_nonTerminal: m_nonTerminals){
      for(string l_varString: m_productionRules[l_nonTerminal]){
        if(l_varString == "epsilon") continue;
        for(int i = 0; i < (int)l_varString.size(); i++){
          if(m_terminals.find(l_varString[i]) != m_terminals.end()){
            continue;
          }
          for(int j = i + 1; j <= (int)l_varString.size(); j++){
            if(j == (int)l_varString.size()){
              for(char l_symbol: l_result[l_nonTerminal]){
                if(l_result[l_varString[i]].find(l_symbol) == l_result[l_varString[i]].end()){
                  l_change = true;
                  l_result[l_varString[i]].insert(l_symbol);
                }
              }
              continue;
            }
            if(m_terminals.find(l_varString[j]) != m_terminals.end()){
              if(l_result[l_varString[i]].find(l_varString[j]) == l_result[l_varString[i]].end()){
                l_change = true;
                l_result[l_varString[i]].insert(l_varString[j]);
              }
              break;
            }
            bool l_hasEpsilon = false;
            for(char l_symbol: l_first[l_varString[j]]){
              if(l_result[l_varString[i]].find(l_symbol) == l_result[l_varString[i]].end()){
                l_change = true;
                l_result[l_varString[i]].insert(l_symbol);
              }
              if(l_symbol == '#') l_hasEpsilon = true;
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