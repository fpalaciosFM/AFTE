#include "AFD_State.hpp"

int AFD_State::count = 0;

AFD_State::AFD_State() {
    this->id = AFD_State::count++;
    this->AFTE_Equivalent = new unordered_set<AFTE_State*>();
    this->AFTEL_Equivalent = new unordered_set<AFTEL_State*>();
}

AFD_State::AFD_State(unordered_set<AFTE_State*> conjunto) : AFD_State() {
    this->AFTE_Equivalent = new unordered_set<AFTE_State*>;
    for (auto& q : conjunto) {
        this->AFTE_Equivalent->insert(q);
    }
}

AFD_State::AFD_State(unordered_set<AFTEL_State*> conjunto) : AFD_State() {
    this->AFTEL_Equivalent = new unordered_set<AFTEL_State*>;
    for (auto& q : conjunto) {
        this->AFTEL_Equivalent->insert(q);
    }
}

bool isStateIn(AFD_State* q, unordered_set<AFD_State*> conjunto) {
    for (auto& x : conjunto) {
        if (q == x) {
            return true;
        }
    }
    return false;
}

AFD_State* getStateFrom(AFD_State* q, unordered_set<AFD_State*> conjunto) {
    for (auto& x : conjunto) {
        if (q == x) {
            return q;
        }
    }
    return 0;
}

bool AFD_State::isEquivalent(AFD_State* q) {
    return *q->AFTE_Equivalent == *this->AFTE_Equivalent;
}