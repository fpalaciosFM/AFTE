#include "AFD_State.hpp"

AFD_State::AFD_State(int id) {
    this->id = id;
    this->final = false;
}

AFD_State::AFD_State(int id, bool final) : AFD_State(id) {
    this->final = final;
}

AFD_State::AFD_State(int id, bool final, unordered_set<AFTE_State*>* conjunto) : AFD_State(id, final) {
    this->AFTE_Equivalent = conjunto;
}

bool AFD_State::isEquivalent(AFD_State* q) {
    bool flag;
    for (auto& p : *(q->AFTE_Equivalent)) {
        flag = false;
        for (auto& r : *(this->AFTE_Equivalent)) {
            if (r == p) {
                flag = true;
                break;
            }
        }
        if (flag == false) {
            return false;
        }
    }
    return true;
}

bool AFD_State::inAFDStateSet(unordered_set<AFD_State*>* AFTE_States) {
    for (auto& state : *(AFTE_States)) {
        if (this->isEquivalent(state)) {
            return true;
        }
    }
    return false;
}

string AFD_State::toString() {
    string s;
    s += "{\n";
    s += "\t id: " + to_string(this->id) + ",\n";
    s += "\t final: " + to_string(this->final) + ",\n";
    s += "\t AFTE_Eq: {";

    // for (auto& x : *(this->AFTE_Equivalent)) {
	// 	s += "\t\t" + x->toString() + "\n";
    // }
}