#ifndef AFTE_HPP
#define AFTE_HPP

#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include "AFTE_State.hpp"

using namespace std;

class AFTE {
   public:
    AFTE_State* initialState;
    AFTE_State* finalState;

    AFTE(AFTE_State* qi, AFTE_State* qf);
    ~AFTE();
    unordered_set<AFTE_State*> RelationR(unordered_set<AFTE_State*> conjunto, char c);
    unordered_set<AFTE_State*> RelationE(unordered_set<AFTE_State*> conjunto);
    unordered_set<AFTE_State*> read(unordered_set<AFTE_State*>, char c);
    unordered_set<AFTE_State*> read(stringstream* ss);
    bool isFinal(unordered_set<AFTE_State*> conjunto);
    bool recognize(stringstream* ss);
    // string toString(AFTE_State* q, unordered_set<AFTE_State*>* statesPrinted);
    string toString();
    string toString(AFTE_State*, unordered_set<AFTE_State*>);
};

#endif /* AFTE_HPP */

// AFTE_State state1(1);
// AFTE_State state2(2);
// AFTE_State state3(3);
// AFTE_State state4(4);
// AFTE_State state5(5);
// AFTE_State state6(6, true);

// string s = "101010";
// stringstream* ss = new stringstream(s);

// state1.addLambda(&state2);
// state2.addLambda(&state3);
// state2.addLambda(&state6);
// state3.addTransition('1', &state4);
// state4.addTransition('0', &state5);
// state5.addLambda(&state2);

// unordered_set<AFTE_State*> conjunto = {&state1};

// AFTE A;
// A.addState(&state1);
// unordered_set<AFTE_State*> result = A.RelationE({&state1});

// cout << A.recognize(ss) << endl;
