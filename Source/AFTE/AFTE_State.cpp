#include "AFTE_State.hpp"

int AFTE_State::count = 0;

AFTE_State::AFTE_State() {
    this->id = AFTE_State::count++;
}

// Se usa un identificador para fines de visualización.
// Se usa una 'bandera' de tipo bool para saber si el estado es final.
AFTE_State::AFTE_State(int id) {
    this->id = id;
}

AFTE_State::~AFTE_State() {}

// Se agrega una transición desde este estado hacia el estado 'q' a traves de la letra 'c'.
// Las transiciones van de un estado hacia un conjunto de estados.
void AFTE_State::addTransition(char c, AFTE_State* q) {
    if (this->transitions.find(c) == this->transitions.end()) {
        unordered_set<AFTE_State*> new_unordered_set({q});
        this->transitions.insert({c, new_unordered_set});
        return;
    }

    this->transitions[c].insert(q);
}

// Se agrega una transición desde este estado hacia el estado 'q' de forma espontanea.
// Las transiciones lambda van de un estado hacia un conjunto de estados.
void AFTE_State::addLambda(AFTE_State* q) {
    this->lambdas.insert(q);
}

// Regresa el conjunto de estados correspondiente a la transición desde este estado a travez de la letra 'c'.
unordered_set<AFTE_State*> AFTE_State::read(char c) {
    if (this->transitions.find(c) == this->transitions.end()) {
        return unordered_set<AFTE_State*>();
    }
    return this->transitions[c];
}

// Devuelve un string con las transiciones y las transiciones espontaneas de este estado.
string AFTE_State::toString() {
    string s = "\tq" + to_string(this->id) + ":";
    s += " {";
    for (auto& transition : this->transitions) {
        for (auto& state : transition.second) {
            s += "\n\t\t";
            s += to_string(this->id);
            s += " --('";
            s += transition.first;
            s += "')--> ";
            s += to_string(state->id);
            s += ",\n";
        };
    }
    for (auto& state : this->lambdas) {
        s += "\n\t\t";
        s += to_string(this->id);
        s += " ---------> ";
        s += to_string(state->id);
        s += ",\n";
    }
    s += "\t}";
    return s;
}

bool isStateIn(AFTE_State* q, unordered_set<AFTE_State*> conjunto) {
    for (auto& state : conjunto) {
        if (q == state) {
            return true;
        }
    }
    return false;
}
