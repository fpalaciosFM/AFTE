#ifndef AFD_HPP
#define AFD_HPP

#include "AFD_State.hpp"

class AFD {
   public:
    unordered_set<AFD_State*> states;		// E(Q)
    AFD_State* initialState;				// E*({q_0})
    unordered_set<AFD_State*> finalStates;	// G
    unordered_map<AFD_State*, unordered_map<char, AFD_State*>> transitions;	// g:E(Q)xZ->E(Q)

    AFD(){};
    ~AFD(){};
};

#endif /* AFD_HPP */