#include "State.hpp"

State::State(int i) {
    this->index = i;
}

State::State(double x, double y, int i) {
    this->x = x;
    this->y = y;
    this->index = i;
}