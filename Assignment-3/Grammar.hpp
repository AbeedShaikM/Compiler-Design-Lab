#ifndef GRAMMAR_HPP
#define GRAMMAR_HPP
#include <bits/stdc++.h>

using namespace std;

// Tyoe-2 CFG

class c_grammar{
  public:
    void f_addNonTerminal(char p_nonTerminal);
    void f_addTerminal(char p_terminal);
    void f_addProductionRule(char p_nonTerminal, string p_varString);
    void f_print();
    void f_removeImmediateLeftRecursion(char p_nonTerminal);
    void f_removeLeftRecursion();
    void f_leftFactor();
    char f_getNotUsedSymbol();
    bool f_hasImmediateRecursion(char p_nonTerminal);
    c_grammar(){}
    void f_removeProductionRule(char p_nonTerminal, string p_varString);
    int f_getParseTree(string& p_grammarString, char p_startSymbol, bool p_isRoot, int& p_transitionID, int p_parentTransactionID, int pos = 0);
    static vector<string> f_getStringsWithSamePrefix(int p_root, vector<map<char, int>>& p_trie, vector<string>& l_ends);
  private:
    set<char> m_terminals;
    set<char> m_nonTerminals;
    map<char, set<string>> m_productionRules;
};

#endif //GRAMMAR_HPP