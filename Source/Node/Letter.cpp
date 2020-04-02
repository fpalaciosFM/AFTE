#include "Letter.hpp"

/**
 * Constructor de Letter
 * 
 * Inicializa Letter con su correspondiente string equivalente en
 * Latex, $0$ o $1$ son los posibles strings 
 * 
 * @param c caracter correspondiente a la letra del alfabeto que
 * 		representara este nodo
 */
Letter::Letter(char c) {
    ch = c;
    texStr = "$";
    texStr += c;
    texStr += "$";
}

Letter::~Letter(void) {}

/**
 * Obtener tipo.
 * 
 * Obtener tipo del nodo invocador.
 *
 * @return enumerador LETTER
 */
int Letter::Type(void) const {
    return LETTER;
}

/**
 * Obtener copia.
 * 
 * Se crea un nuevo nodo Letter con la misma letra del nodo invocador.
 * 
 * @return apuntador a nodo con copia del nodo invocador
 */
Node* Letter::Copy(void) const {
    return new Letter(ch);
}

/**
 * Simplificar nodo.
 * 
 * Los nodos tipo LETTER no pueden simplificarse mas.
 * 
 * @return apuntador a nodo con copia del nodo invocador
 */
Node* Letter::Simp(void) const {
    return Copy();
}

/**
 * Imprimir el equivalente del nodo invocador en texto crudo.
 * 
 * @param os canal de salida
 * @return canal de salida
 */
ostream& Letter::Print(ostream& os) const {
    return os << ch;
}

/**
 * Generar AFTE.
 * 
 * Funcion recursiva (usada en Node::toAFTE(double,double) y polimorfica
 * para generar el AFTE correspondiente a la expresion regular del
 * programa en ejecucion. En este caso el AFTE de un nodo de tipo LETTER
 * consta de dos nodos unidos por una arista rotulada con la
 * correspondiente letra del nodo invocador.
 * 
 * @param x abscisa al origen del punto de referencia del AFTE
 * @param y ordenada al origen del punto de referencia del AFTE
 * 
 * @return AFTE que representa al nodo invocador
 */
AFTE Letter::toAFTE(double x, double y) {
    AFTE_State* qi = new AFTE_State(x, y);
    AFTE_State* qf = new AFTE_State(x + N + E, y);
    qi->addTransition(this->ch, qf);
    return AFTE(qi, qf);
}