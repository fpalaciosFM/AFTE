#ifndef STATE_HPP
#define STATE_HPP

class State {
   public:
    int index;
    double x;
    double y;

    State(int i);
    State(double x, double y, int i);
    ~State();
};

#endif /* STATE_HPP */