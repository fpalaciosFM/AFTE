#include "AFTE.hpp"

AFTE::AFTE() {}

AFTE::~AFTE() {}

// Agrega un estado al AFTE.
// Lo inserta como final si la bandera 'final' del estado es verdadera.
// En otro caso lo inserta como inicial.
void AFTE::addState(AFTE_State* q) {
    if (q->final) {
        this->finalStates.insert(q);
    } else {
        this->initialStates.insert(q);
    }
}

// Relacion de transiciones
unordered_set<AFTE_State*> AFTE::RelationR(unordered_set<AFTE_State*> conjunto, char c) {
    unordered_set<AFTE_State*> conjuntoReturn;

    for (auto& q : conjunto) {
        for (auto& p : q->read(c)) {
            conjuntoReturn.insert(p);
        }
    }

    return conjuntoReturn;
}

// Relacion de transiciones espontaneas
unordered_set<AFTE_State*> AFTE::RelationE(unordered_set<AFTE_State*> conjunto) {
    unordered_set<AFTE_State*> conjuntoEC = conjunto;
    unordered_set<AFTE_State*> conjuntoEi;
    unordered_set<AFTE_State*> conjuntoEii = conjunto;
    int oldLength;

    do {
        conjuntoEi = conjuntoEii;
        conjuntoEii = unordered_set<AFTE_State*>();
        oldLength = conjuntoEC.size();

        for (auto& state : conjuntoEi) {
            for (auto& q : state->lambdas) {
                conjuntoEii.insert(q);
            }
        }

        for (auto& state : conjuntoEii) {
            conjuntoEC.insert(state);
        }
    } while (conjuntoEC.size() != oldLength);

    return conjuntoEC;
}

// Funcion de transicion.
unordered_set<AFTE_State*> AFTE::read(unordered_set<AFTE_State*> conjunto, char c) {
    return this->RelationE(this->RelationR(this->RelationE(conjunto), c));
}

// Funcion de transicion iterada.
unordered_set<AFTE_State*> AFTE::read(stringstream* ss) {
    unordered_set<AFTE_State*> result = this->RelationE(this->initialStates);
    char c;

    if (ss->good() && ss->peek() >= 0) {
        result = this->read(this->initialStates, ss->get());
    }

    while (ss->good() && ss->peek() >= 0) {
        c = ss->get();
        result = this->read(result, c);
    }

    return result;
}

// Verifica si un conjunto de estados contiene un estado final.
bool AFTE::isFinal(unordered_set<AFTE_State*> conjunto) {
    for (auto& q : conjunto) {
        if (q->final) {
            return true;
        }
    }
    return false;
}

// Verifica si la cadena 'ss' es reconocida por el AFTE.
bool AFTE::recognize(stringstream* ss) {
    unordered_set<AFTE_State*> result = this->read(ss);
    return this->isFinal(result);
}