#include "AFTEL.hpp"

AFTEL::AFTEL(AFTEL_State* qi, AFTEL_State* qf) {
    this->initialState = qi;
    this->finalState = qf;
}

AFTEL::~AFTEL() {}

// Relacion de transiciones
unordered_set<AFTEL_State*> AFTEL::RelationR(unordered_set<AFTEL_State*> conjunto, char c) {
    unordered_set<AFTEL_State*> conjuntoReturn;

    for (auto& q : conjunto) {
        for (auto& p : q->read(c)) {
            conjuntoReturn.insert(p);
        }
    }

    return conjuntoReturn;
}

// ******************
// ** AFTE Methods **
// ******************

// Relacion de transiciones espontaneas
unordered_set<AFTEL_State*> AFTEL::RelationE(unordered_set<AFTEL_State*> conjunto) {
    unordered_set<AFTEL_State*> conjuntoEC = conjunto;
    unordered_set<AFTEL_State*> conjuntoEi;
    unordered_set<AFTEL_State*> conjuntoEii = conjunto;
    int oldLength;

    do {
        conjuntoEi = conjuntoEii;
        conjuntoEii = unordered_set<AFTEL_State*>();
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
unordered_set<AFTEL_State*> AFTEL::read(unordered_set<AFTEL_State*> conjunto, char c) {
    return this->RelationE(this->RelationR(this->RelationE(conjunto), c));
}

// Funcion de transicion iterada.
unordered_set<AFTEL_State*> AFTEL::read(stringstream* ss) {
    unordered_set<AFTEL_State*> inputSet = {this->initialState};
    unordered_set<AFTEL_State*> result = this->RelationE(inputSet);
    char c;

    if (ss->good() && ss->peek() >= 0) {
        result = this->read(inputSet, ss->get());
    }

    while (ss->good() && ss->peek() >= 0) {
        c = ss->get();
        result = this->read(result, c);
    }

    return result;
}

// Verifica si un conjunto de estados contiene un estado final.
bool AFTEL::isFinal(unordered_set<AFTEL_State*> conjunto) {
    for (auto& q : conjunto) {
        if (this->finalState == q) {
            return true;
        }
    }
    return false;
}

// Verifica si la cadena 'ss' es reconocida por el AFTEL.
bool AFTEL::recognize(stringstream* ss) {
    unordered_set<AFTEL_State*> result = this->read(ss);
    return this->isFinal(result);
}

// Imprime todos los estados del AFTEL
string AFTEL::toString() {
    string s = "{\n";
    unordered_set<AFTEL_State*> statesPrinted;
    s += this->toString(this->initialState, statesPrinted);
    s += "\n}";
    return s;
}

// Imprime un unico estado del AFTEL,
// Despues se imprimen los estados que tengan una transicion desde el estado q.
string AFTEL::toString(AFTEL_State* q, unordered_set<AFTEL_State*> statesPrinted) {
    string s;
    if (isStateIn(q, statesPrinted)) {
        return s;
    }

    s += q->toString() + ",\n";
    statesPrinted.insert(q);

    for (auto& p : q->transitions) {
        for (auto& r : p.second) {
            s += this->toString(r, statesPrinted);
        }
    }

    for (auto& p : q->lambdas) {
        s += this->toString(p, statesPrinted);
    }

    return s;
}

// *******************
// ** Latex Methods **
// *******************
