#include "AFTE_State.hpp"

// Se usa un identificador para fines de visualización.
// Se usa una 'bandera' de tipo bool para saber si el estado es final.
AFTE_State::AFTE_State(int id) {
    this->final = false;
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

// Imprime las transiciones y las transiciones espontaneas de este estado.
ostream& AFTE_State::print(ostream& os) {
    cout << '{' << endl;
    for (auto& transition : this->transitions) {
        for (auto& state : transition.second) {
            os << "\t" << this->id << " --('" << transition.first << "')--> " << state->id << ',' << endl;
        }
    }
    for (auto& state : this->lambdas) {
        os << "\t" << this->id << " ---------> " << state->id << ',' << endl;
    }
    cout << '}';
    return os;
}

string AFTE_State::toString() {
    string s = "{ ";
    for (auto& transition : this->transitions) {
        for (auto& q : transition.second) {
            s += "(" + to_string(this->id) + ",'" + transition.first + "'," + to_string(q->id) + ") ";
        }
    }
    for (auto& lambda : this->lambdas) {
        s += "(" + to_string(this->id) + ",'" + to_string(lambda->id) + " ";
    }
}