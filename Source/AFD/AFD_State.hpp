#ifndef AFD_STATE_HPP
#define AFD_STATE_HPP

#include "../AFTE/AFTEL.hpp"

class AFD_State {
   public:
    static int count;
    int id;
    unordered_set<AFTE_State*>* AFTEL_Equivalent;

    AFD_State();
    AFD_State(unordered_set<AFTE_State*> conjunto);
    ~AFD_State(){};
};

bool isStateIn(AFD_State* q, unordered_set<AFD_State*> conjunto);

#endif /* AFD_STATE_HPP */