#include "AFTE_State.hpp"

AFTE_State::AFTE_State(int id) {
    this->final = false;
    this->id = id;
}

AFTE_State::~AFTE_State() {}

void AFTE_State::addTransition(char c, AFTE_State* q) {
    if (this->transitions.find(c) == this->transitions.end()) {
        unordered_set<AFTE_State*> new_unordered_set({q});
        this->transitions.insert({c, new_unordered_set});
        return;
    }

    this->transitions[c].insert(q);
}

unordered_set<AFTE_State*> AFTE_State::read(char c) {
    return this->transitions[c];
}

ostream& AFTE_State::print(ostream& os) {
    cout << '{' << endl;
    for (auto& transition : this->transitions) {
        for (auto& state : transition.second) {
            os << "\t" << this->id << " --('" << transition.first << "')--> " << state->id << ',' << endl;
        }
    }
    cout << '}';
    return os;
}