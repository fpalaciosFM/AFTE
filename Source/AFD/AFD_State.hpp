#ifndef AFD_STATE_HPP
#define AFD_STATE_HPP

#include "../AFTE/AFTE.hpp"
#include "../AFTE_Latex/AFTEL.hpp"

class AFD_State {
   public:
    static int count;
    int id;
    unordered_set<AFTE_State*>* AFTE_Equivalent;

    AFD_State();
    AFD_State(unordered_set<AFTE_State*> conjunto);
    AFD_State(unordered_set<AFTEL_State*> conjunto);
    ~AFD_State(){};

    bool isEquivalent(AFD_State*);
};

bool isStateIn(AFD_State* q, unordered_set<AFD_State*> conjunto);
AFD_State* getStateFrom(AFD_State* q, unordered_set<AFD_State*> conjunto);

#endif /* AFD_STATE_HPP */