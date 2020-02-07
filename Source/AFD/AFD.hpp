#ifndef AFD_HPP
#define AFD_HPP

#include "AFD_State.hpp"

class AFD {
   public:
    AFD_State* initialState;
    unordered_set<AFD_State*> finalStates;
    unordered_map<AFD_State*, unordered_map<char, AFD_State*>> transitions;

    AFD(){};
    ~AFD(){};
    void addTransition(AFD_State* q, char c, AFD_State* p);
    string toString();

    // AFD_State* read(char c);
    AFD_State* read(stringstream* ss);
    bool recognize(stringstream* ss);
};

#endif /* AFD_HPP */