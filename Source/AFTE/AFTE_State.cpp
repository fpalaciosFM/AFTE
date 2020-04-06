#include "AFTE_State.hpp"

/**
 * Contador de estados.
 * 
 * Contador utilizado para generar los identificadores de los estados.
 */
int AFTE_State::count = 0;

/** 
 * Constructor con las coordenadas del estado para su impresion en LaTeX.
 */
AFTE_State::AFTE_State(double x, double y) {
    this->id = AFTE_State::count++;
    this->x = x;
    this->y = y;
}

/**
 * Constructor sin parametros.
*/
AFTE_State::AFTE_State() : AFTE_State(0, 0) {
}

AFTE_State::~AFTE_State() {}

/**
 * Agregar transicion.
 * 
 * Se agrega una transición desde el estado invocador hacia el estado
 * 'q' a traves de la letra 'c'. Las transiciones van de un estado hacia
 * un conjunto de estados.
 * 
 * @param c letra de la transicion
 * @param q estado destino de la transicion
*/
void AFTE_State::addTransition(char c, AFTE_State* q) {
    if (this->transitions.find(c) == this->transitions.end()) {
        unordered_set<AFTE_State*> new_unordered_set({q});
        this->transitions.insert({c, new_unordered_set});
        return;
    }

    this->transitions[c].insert(q);
}

/**
 * Se agrega una transicion espontanea desde el estado invocador hacia
 * el estado 'q'. Las transiciones lambda van de un estado hacia un
 * conjunto de estados.
 * 
 * @param q estado destino de la transicion espontanea
*/
void AFTE_State::addLambda(AFTE_State* q) {
    this->lambdas.insert(q);
}

/**
 * Regresa el conjunto de estados correspondiente a la transición desde
 * el estado invocador a travez de la letra 'c'.
 * 
 * @return conjunto de estados correspondiente a las transiciones desde
 *      estado a traves de la letra 'c'.
*/
unordered_set<AFTE_State*> AFTE_State::read(char c) {
    if (this->transitions.find(c) == this->transitions.end()) {
        return unordered_set<AFTE_State*>();
    }
    return this->transitions[c];
}

/**
 * Conversion a texto.
 * 
 * @return texto con resumen de informacion del estado invocador
*/
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

/**
 * Pertenencia de un estado en un conjunto.
 * 
 * Revisa si el primer parametro es un elemento del conjunto del segundo
 * parametro.
 * 
 * @param q estado para verificar pertenencia
 * @param conjunto de prueba
 * 
 * @return true si el estado q pertenece al conjunto, false en caso
 *      contrario
 */
bool isStateIn(AFTE_State* q, unordered_set<AFTE_State*> conjunto) {
    for (auto& state : conjunto) {
        if (q == state) {
            return true;
        }
    }
    return false;
}