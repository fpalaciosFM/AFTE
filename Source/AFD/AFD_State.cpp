#include "AFD_State.hpp"

/**
 * Contador de estados.
 * 
 * Contador utilizado para generar los identificadores de los estados.
 */
int AFD_State::count = 0;

/**
 * Constructor de AFD_State sin parametros.
 * 
 * Inicializa el estado con el correspondiente identificador usando
 * 'count'.
 * Inicializa el estado equivalente en AFTE como un conjunto de estados
 * vacio.
 */
AFD_State::AFD_State() {
    this->id = AFD_State::count++;
    this->AFTE_Equivalent = new unordered_set<AFTE_State*>();
}

/**
 * Constructor con AFTE equivalente.
 * 
 * Guarda al conjunto de estados de AFTE del parametro como equivalente
 * del estado en construccion.
 * 
 * @param conjunto de estados de AFTE equivalente 
 */
AFD_State::AFD_State(unordered_set<AFTE_State*> conjunto)
    : AFD_State() {
    this->AFTE_Equivalent = new unordered_set<AFTE_State*>;
    for (auto& q : conjunto) {
        this->AFTE_Equivalent->insert(q);
    }
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
bool isStateIn(AFD_State* q, unordered_set<AFD_State*> conjunto) {
    for (auto& x : conjunto) {
        if (q == x) {
            return true;
        }
    }
    return false;
}