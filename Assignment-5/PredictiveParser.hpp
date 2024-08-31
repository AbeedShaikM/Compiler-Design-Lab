#ifndef PREDICTIVE_PARSERHPP
#define PREDICTIVE_PARSERHPP
#include "../Assignment-4/Grammar.hpp"

class c_predictiveParser: public c_grammar{
  public:
    bool f_isAccepted(string p_inputString, char p_startSymbol);
    c_predictiveParser();
    void f_printParseTable(char p_startSymbol);
  private:
    map<char, map<char, string>> m_table;
    void f_populateTable(char p_startSymbol);
};

#endif // PREDICTIVE_PARSERHPP