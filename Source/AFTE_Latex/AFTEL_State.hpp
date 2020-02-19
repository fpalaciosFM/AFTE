#ifndef AFTE_LATEX_STATE_HPP
#define AFTE_LATEX_STATE_HPP

#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class AFTEL_State {
   public:
    static int count;

    // AFTE Attributes
    unordered_map<char, unordered_set<AFTEL_State*>> transitions;
    unordered_set<AFTEL_State*> lambdas;
    int id;

    // Latex Attributes
    string label;
    double x;
    double y;

    AFTEL_State();
    AFTEL_State(double x, double y);
    ~AFTEL_State();

    // AFTE Methods
    void addTransition(char c, AFTEL_State* q);
    void addLambda(AFTEL_State* q);
    unordered_set<AFTEL_State*> read(char);
    string toString();

    // Latex Methods
};

bool isStateIn(AFTEL_State* q, unordered_set<AFTEL_State*> conjunto);

#endif /* AFTE_LATEX_STATE_HPP */