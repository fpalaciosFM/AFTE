#ifndef AFTE_LATEX_STATE_HPP
#define AFTE_LATEX_STATE_HPP

#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class AFTE_State {
   public:
    static int count;

    // AFTE Attributes
    unordered_map<char, unordered_set<AFTE_State*>> transitions;
    unordered_set<AFTE_State*> lambdas;
    int id;

    // Latex Attributes
    string label;
    double x;
    double y;

    AFTE_State();
    AFTE_State(double x, double y);
    ~AFTE_State();

    // AFTE Methods
    void addTransition(char c, AFTE_State* q);
    void addLambda(AFTE_State* q);
    unordered_set<AFTE_State*> read(char);
    string toString();

    // Latex Methods
};

bool isStateIn(AFTE_State* q, unordered_set<AFTE_State*> conjunto);

#endif /* AFTE_LATEX_STATE_HPP */