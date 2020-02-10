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

// AFTE_State q0;
// AFTE_State q1;
// AFTE_State q2;
// AFTE_State q3;
// AFTE_State q4;

// q0.addLambda(&q1);
// q1.addLambda(&q4);
// q1.addLambda(&q2);
// q2.addTransition('1', &q3);
// q3.addLambda(&q1);

// AFTE M(&q0, &q4);

// cout << M.toString() << endl;

// string s = "11111";
// stringstream* ss = new stringstream(s);

// cout << M.recognize(ss) << endl;