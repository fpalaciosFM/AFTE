#include "AFD_State.hpp"

int AFD_State::count = 0;

AFD_State::AFD_State() {
    this->id = AFD_State::count++;
    this->AFTEL_Equivalent = new unordered_set<AFTE_State*>();
}

AFD_State::AFD_State(unordered_set<AFTE_State*> conjunto) : AFD_State() {
    this->AFTEL_Equivalent = new unordered_set<AFTE_State*>;
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