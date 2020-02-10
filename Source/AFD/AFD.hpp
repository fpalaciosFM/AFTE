#ifndef AFD_HPP
#define AFD_HPP

#include "AFD_State.hpp"

class AFD {
   public:
    unordered_set<AFD_State*> states;
    AFD_State* initialState;
    unordered_set<AFD_State*> finalStates;
    unordered_map<AFD_State*, unordered_map<char, AFD_State*>> transitions;

    AFD(){};
    ~AFD(){};
};

#endif /* AFD_HPP */