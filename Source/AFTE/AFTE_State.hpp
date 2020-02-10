#ifndef AFTE_STATE_HPP
#define AFTE_STATE_HPP

#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class AFTE_State {
   public:
    static int count;
    unordered_map<char, unordered_set<AFTE_State*>> transitions;
    unordered_set<AFTE_State*> lambdas;
    int id;

    AFTE_State();
    AFTE_State(int id);
    ~AFTE_State();

    unordered_set<AFTE_State*> read(char);
    void addTransition(char c, AFTE_State* q);
    void addLambda(AFTE_State* q);
    string toString();
};

bool isStateIn(AFTE_State* q, unordered_set<AFTE_State*> conjunto);

#endif /* AFTE_STATE_HPP */
