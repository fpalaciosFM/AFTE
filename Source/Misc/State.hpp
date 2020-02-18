#ifndef STATE_HPP
#define STATE_HPP

#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

class State {
   public:
    static int count;
    string extra;
    int index;
    double x;
    double y;

    State(int i);
    State(int i, std::string extra);
    ~State();

    string toLatex();
    string toLatex(State q);
    string toLatexClosure(State q, int out, int in);
    string toLatex(std::string sigma, State q);
    void setPos(double, double);
    void setIndex(int i);
};

#endif /* STATE_HPP */