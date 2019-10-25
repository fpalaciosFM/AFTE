#ifndef STATE_HPP
#define STATE_HPP

#include <string>

class State {
   public:
    std::string extra;
    int index;
    double x;
    double y;

    State(int i);
    State(int i, std::string extra);
    ~State();

    std::string toLatex();
    std::string toLatex(State q);
    std::string toLatex(std::string sigma, State q);
    void setPos(double, double);
    void setIndex(int i);
};

#endif /* STATE_HPP */