#include "Empty.hpp"

/**
 * Constructor de nodo Empty.
 * 
 * Inicializa el nodo con el string equivalente en Latex.
 */
Empty::Empty() {
    texStr = "$\\emptyset$";
}

Empty::~Empty(void) {}

/**
 * Obtener tipo.
 * 
 * Obtener tipo del nodo invocador.
 * 
 * @return enumerador EMPTY
 */
int Empty::Type(void) const {
    return EMPTY;
}

/**
 * Obtener copia.
 * 
 * Se crea un nuevo nodo Empty.
 * 
 * @return apuntador a nodo con copia del nodo invocador
 */
Node* Empty::Copy(void) const {
    return new Empty();
}

/**
 * Simplificar nodo.
 * 
 * Los nodos tipo EMPTY no pueden simplificarse mas.
 * 
 * @return apuntador a nodo con copia del nodo invocador
 */
Node* Empty::Simp(void) const {
    return Copy();
}

/**
 * Imprimir el equivalente del nodo invocador en texto crudo.
 *
 * Imprime el string "empty".
 *  
 * @param os canal de salida
 * @return canal de salida
*/
ostream& Empty::Print(ostream& os) const {
    return os << "empty";
}

/**
 * Generar AFTE.
 * 
 * Funcion recursiva (usada en Node::toAFTE(double,double)) y
 * polimorfica para generar el AFTE correspondiente a la expresion
 * regular del programa en ejecucion. En este caso el AFTE de un nodo de
 * tipo EMPTY consta de dos nodos sin union alguna, representando un 
 * AFTE que no puede reconocer ninguna palabra.
 * 
 * @param x abscisa al origen del punto de referencia del AFTE
 * @param y ordenada al origen del punto de referencia del AFTE
 * 
 * @return AFTE que representa al nodo invocador
 */
AFTE Empty::toAFTE(double x, double y) {
    AFTE_State* qi = new AFTE_State(x, y);
    AFTE_State* qf = new AFTE_State(x + N + E, y);
    return AFTE(qi, qf);
}