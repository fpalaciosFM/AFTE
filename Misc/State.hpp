#ifndef STATE_HPP
#define STATE_HPP

#include <string>

class State {
   public:
    int index;
    double x;
    double y;

    State(int i);
    State(double x, double y, int i);
    ~State();

    std::string toLatex(std::string extra);
    std::string toLatex();
};

#endif /* STATE_HPP */