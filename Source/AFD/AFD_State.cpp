#include "AFD_State.hpp"

AFD_State::AFD_State(int id) {
    this->id = id;
    this->final = false;
}

AFD_State::AFD_State(int id, bool final) : AFD_State(id) {
    this->final = final;
}

AFD_State::AFD_State(int id, bool final, unordered_set<AFTE_State*> conjunto) : AFD_State(id, final) {
    this->AFTE_Equivalent = conjunto;
}