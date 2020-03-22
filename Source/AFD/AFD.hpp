#ifndef AFD_HPP
#define AFD_HPP

#include "../AFTE/AFTEL.hpp"
#include "AFD_State.hpp"

class AFD {
   public:
    unordered_set<char> Sigma = {'1', '0'};                                  // El alfabeto \Sigma
    unordered_set<AFD_State*> states;                                        // E(Q)
    unordered_set<AFD_State*> finalStates;                                   // G
    unordered_map<AFD_State*, unordered_map<char, AFD_State*>> transitions;  // g : E(Q)xZ -> E(Q)
    AFD_State* initialState;                                                 // E*({q_0})

    AFD(){};
    AFD(AFTE);
    ~AFD(){};

    void makeTransitions(AFD_State*, AFTE M);
    void addState(AFD_State*, AFTE);
    AFD_State* findEquivalentL(AFD_State*);
    string toString();
};

#endif /* AFD_HPP */