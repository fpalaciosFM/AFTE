#include "AFTEL_State.hpp"

// count se utiliza para no tener que darle nombre a cada estado, se genera automaticamente
int AFTEL_State::count = 0;

// Constructor que asigna el identificador
AFTEL_State::AFTEL_State() {
    this->id = AFTEL_State::count++;
}

// Constructor con las coordenadas del estado para su impresion en LaTeX.
AFTEL_State::AFTEL_State(double x, double y) : AFTEL_State() {
    this->x = x;
    this->y = y;
}

AFTEL_State::~AFTEL_State() {}

// ******************
// ** AFTE Methods **
// ******************

// Se agrega una transición desde este estado hacia el estado 'q' a traves de la letra 'c'.
// Las transiciones van de un estado hacia un conjunto de estados.
void AFTEL_State::addTransition(char c, AFTEL_State* q) {
    if (this->transitions.find(c) == this->transitions.end()) {
        unordered_set<AFTEL_State*> new_unordered_set({q});
        this->transitions.insert({c, new_unordered_set});
        return;
    }

    this->transitions[c].insert(q);
}

// Se agrega una transición desde este estado hacia el estado 'q' de forma espontanea.
// Las transiciones lambda van de un estado hacia un conjunto de estados.
void AFTEL_State::addLambda(AFTEL_State* q) {
    this->lambdas.insert(q);
}

// Regresa el conjunto de estados correspondiente a la transición desde este estado a travez de la letra 'c'.
unordered_set<AFTEL_State*> AFTEL_State::read(char c) {
    if (this->transitions.find(c) == this->transitions.end()) {
        return unordered_set<AFTEL_State*>();
    }
    return this->transitions[c];
}

// Devuelve un string con las transiciones y las transiciones espontaneas de este estado.
string AFTEL_State::toString() {
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

// Funcion para verificar si un estado 'q' es un elemento del conjunto 'conjunto'.
bool isStateIn(AFTEL_State* q, unordered_set<AFTEL_State*> conjunto) {
    for (auto& state : conjunto) {
        if (q == state) {
            return true;
        }
    }
    return false;
}

// *******************
// ** Latex Methods **
// *******************
