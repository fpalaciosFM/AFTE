#include "AFD.hpp"

void AFD::addTransition(AFD_State* q, char c, AFD_State* p) {
    unordered_map<char, AFD_State*> map_insert;
    map_insert.insert({c, p});

    if (this->transitions.empty()) {
        this->initialState = q;
    }

    if (q->final) {
        this->finalStates.insert(q);
    }

    if (this->transitions.find(q) == this->transitions.end()) {
        this->transitions.insert({q, map_insert});
    } else {
        if (this->transitions[q].find(c) == this->transitions[q].end()) {
            this->transitions[q].insert({c, p});
        } else {
            this->transitions[q][c] = p;
        }
    }
}

string AFD::toString() {
    string s = "{\n";
    for (auto& elem : this->transitions) {
        for (auto& subelem : elem.second) {
            s += "  f(";
            s += to_string(elem.first->id);
            s += ",\'";
            s += subelem.first;
            s += "\')=";
            s += to_string(subelem.second->id);

            if (this->initialState == elem.first) {
                s += "  State ";
                s += to_string(elem.first->id);
                s += " is initial.";
            }

            if (elem.first->final) {
                s += "  State ";
                s += to_string(elem.first->id);
                s += " is final.";
            }

            s += '\n';
        }
    }
    s += '}';

    return s;
}

AFD_State* AFD::read(stringstream* ss) {
    AFD_State* state_i = this->initialState;
    char c;
    int i = 0;

    while (ss->good() && ss->peek() >= 0) {
        c = ss->get();
        i++;
        state_i = this->transitions[state_i][c];
    }

    return state_i;
}

bool AFD::recognize(stringstream* ss) {
    AFD_State* result = this->read(ss);
    return result->final;
}