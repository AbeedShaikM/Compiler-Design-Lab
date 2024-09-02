#ifndef GRAMMAR_HPP
#define GRAMMAR_HPP
#include <bits/stdc++.h>

using namespace std;

// Tyoe-2 CFG

class c_grammar{
  public:
    void f_addNonTerminal(string p_nonTerminal);
    void f_addTerminal(string p_terminal);
    void f_addProductionRule(string p_nonTerminal, string p_varString);
    void f_print();
    c_grammar();
    void f_removeLeftRecursion();
    void f_leftFactor();
    string f_getNewSymbol(string p_symbol);
    bool f_hasImmediateRecursion(string p_nonTerminal);
    void f_removeProductionRule(string p_nonTerminal, string p_varString);
    bool f_getParseTree(string& p_grammarString, string p_startSymbol);
    static vector<string> f_getStringsWithSamePrefix(int p_root, vector<map<string, int>>& p_trie, vector<string>& l_ends);
    map<string, set<string>> f_getFirst();
    map<string, set<string>> f_getFollow(string p_startSymbol);
  protected:
    set<string> m_terminals;
    set<string> m_nonTerminals;
    map<string, set<string>> m_productionRules;
    vector<string> f_getSymbols(string p_productionRule);
    vector<map<char, int>> m_trie;
    vector<int> m_isEnd;
  private:
    void f_addString(string p_string);
    void f_removeImmediateLeftRecursion(string p_nonTerminal);
    bool f_isAccepted(vector<string> p_grammarString, stack<string> p_currentSentForm, int pos);
};

#endif //GRAMMAR_HPP