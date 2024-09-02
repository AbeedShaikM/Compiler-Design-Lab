#ifndef PREDICTIVE_PARSERHPP
#define PREDICTIVE_PARSERHPP
#include "../Assignment-4/Grammar.hpp"

class c_predictiveParser: public c_grammar{
  public:
    bool f_isAccepted(string p_inputString, string p_startSymbol);
    c_predictiveParser();
    void f_printParseTable(string p_startSymbol, string p_outputFileName);
  private:
    map<string, map<string, string>> m_table;
    void f_populateTable(string p_startSymbol);
};

#endif // PREDICTIVE_PARSERHPP