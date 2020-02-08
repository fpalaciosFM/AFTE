#ifndef AFD_STATE_HPP
#define AFD_STATE_HPP

#include "../AFTE/AFTE.hpp"

class AFD_State {
   public:
    int id;
    bool final;
    unordered_set<AFTE_State*>* AFTE_Equivalent;

    AFD_State(int id);
    AFD_State(int id, bool final);
    AFD_State(int id, bool final, unordered_set<AFTE_State*>* conjunto);
    ~AFD_State(){};

    bool isEquivalent(AFD_State*);
    bool isEquivalent(AFTE_State*);
    bool inAFDStateSet(unordered_set<AFD_State*>* AFTE_States);
    string toString();
};

#endif /* AFD_STATE_HPP */