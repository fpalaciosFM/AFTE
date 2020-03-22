#ifndef AFTE_LATEX_HPP
#define AFTE_LATEX_HPP

#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include "AFTE_State.hpp"

using namespace std;

class AFTE {
   public:
    // AFTE Attributes
    // unordered_set<char> Sigma;
    // unordered_set<AFTE_State*> states;
    AFTE_State* initialState;
    AFTE_State* finalState;

    AFTE(AFTE_State* qi, AFTE_State* qf);
    ~AFTE();

    // AFTE Methods
    unordered_set<AFTE_State*> RelationR(unordered_set<AFTE_State*> conjunto, char c);
    unordered_set<AFTE_State*> RelationE(unordered_set<AFTE_State*> conjunto);
    unordered_set<AFTE_State*> read(unordered_set<AFTE_State*>, char c);
    unordered_set<AFTE_State*> read(stringstream* ss);
    bool isFinal(unordered_set<AFTE_State*> conjunto);
    bool recognize(stringstream* ss);
    string toString();
    string toString(AFTE_State*, unordered_set<AFTE_State*>);

    // Latex Methods
    string toDiagram();
    void toDiagram(AFTE_State*, unordered_set<AFTE_State*>*, string* nodes, string* edges);
};

#endif /* AFTE_LATEX_HPP */