#ifndef AFTE_HPP
#define AFTE_HPP

#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include "AFTE_State.hpp"

using namespace std;

class AFTE {
   public:
    unordered_set<AFTE_State*> initialStates;
    unordered_set<AFTE_State*> finalStates;

    AFTE();
    ~AFTE();

    void addState(AFTE_State* q);

    //    private:
    unordered_set<AFTE_State*> RelationR(unordered_set<AFTE_State*> conjunto, char c);
    unordered_set<AFTE_State*> RelationE(unordered_set<AFTE_State*> conjunto);
    unordered_set<AFTE_State*> read(unordered_set<AFTE_State*>, char c);
    unordered_set<AFTE_State*> read(stringstream* ss);
    bool isFinal(unordered_set<AFTE_State*> conjunto);
    bool recognize(stringstream* ss);
};

#endif /* AFTE_HPP */