#include "State.hpp"

State::State(int i) {
    this->index = i;
}

State::State(int i, std::string extra) {
    this->index = i;
    this->extra = extra;
}

State::~State() {}

std::string State::toLatex() {
    std::string s;
    s += "\t\\node[state";

    if (extra.compare("")) {
        s += ",";
        s += extra;
    }

    s += "] (" + std::to_string(index) + ") at (" + std::to_string(x) + "," + std::to_string(y) + ") {$q_{" + std::to_string(index) + "}$};\n";

    return s;
}

std::string State::toLatex(State q) {
    std::string s;
    s = "\t(" + std::to_string(index) + ") edge (" + std::to_string(q.index) + ")\n";
    return s;
}

std::string State::toLatex(std::string sigma, State q) {
    std::string s;
    s = "\t(" + std::to_string(index) + ") edge[above] node{" + sigma + "} (" + std::to_string(q.index) + ")\n";
    return s;
}

std::string State::toLatexClosure(State q, int out, int in){
    std::string s;
    s = "(" + std::to_string(index) + ") edge[out=" + std::to_string(out) + ", in=" + std::to_string(in) + "] (" + std::to_string(q.index) + ")" ;
    return s;
}

void State::setPos(double x, double y) {
    this->x = x;
    this->y = y;
}

void State::setIndex(int i) {
    this->index = i;
}