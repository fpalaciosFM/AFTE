#ifndef AFTE_LATEX_HPP
#define AFTE_LATEX_HPP

#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include "AFTEL_State.hpp"

using namespace std;

class AFTEL {
   public:
    // AFTE Attributes
    unordered_set<char> Sigma;
    AFTEL_State* initialState;
    AFTEL_State* finalState;

    AFTEL(AFTEL_State* qi, AFTEL_State* qf);
    ~AFTEL();

    // AFTE Methods
    unordered_set<AFTEL_State*> RelationR(unordered_set<AFTEL_State*> conjunto, char c);
    unordered_set<AFTEL_State*> RelationE(unordered_set<AFTEL_State*> conjunto);
    unordered_set<AFTEL_State*> read(unordered_set<AFTEL_State*>, char c);
    unordered_set<AFTEL_State*> read(stringstream* ss);
    bool isFinal(unordered_set<AFTEL_State*> conjunto);
    bool recognize(stringstream* ss);
    string toString();
    string toString(AFTEL_State*, unordered_set<AFTEL_State*>);

    // Latex Methods
};

#endif /* AFTE_LATEX_HPP */