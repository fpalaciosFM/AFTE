#include "State.hpp"

State::State(int i) {
    this->index = i;
}

State::State(double x, double y, int i) {
    this->x = x;
    this->y = y;
    this->index = i;
}

State::~State(){}

std::string State::toLatex(std::string extra) {
    std::string s;
    s += "\t\\node[state";
    
    if (extra.compare("")) {
        s += ",";
        s += extra;
    }

    s += "] (" + std::to_string(index) + ") at (" + std::to_string(x) + "," + std::to_string(y) + ") {$q_{" + std::to_string(index) + "}$};\n";
    
    return s;
}

std::string State::toLatex(){
    return toLatex("");
}