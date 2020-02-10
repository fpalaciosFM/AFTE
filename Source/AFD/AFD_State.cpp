#include "AFD_State.hpp"

int AFD_State::count = 0;

AFD_State::AFD_State(int id) {
    this->id = id;
}

AFD_State::AFD_State(int id, unordered_set<AFTE_State*> conjunto) : AFD_State(id) {
    this->AFTE_Equivalent = conjunto;
}