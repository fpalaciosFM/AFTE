#include "Lambda.hpp"

/**
 * Constructor de nodo Lambda.
 * 
 * Inicializa el nodo con el string equivalente en Latex.
 */
Lambda::Lambda(void) {
    texStr = "$\\lambda$";
};

Lambda::~Lambda(void){};

/**
 * Obtener tipo.
 * 
 * Obtener tipo del nodo invocador.
 * 
 * @return enumerador LAMBDA
 */
int Lambda::Type(void) const {
    return LAMBDA;
}

/**
 * Obtener copia.
 * 
 * Se crea un nuevo nodo Lambda.
 * 
 * @return apuntador a nodo con copia del nodo invocador
 */
Node* Lambda::Copy(void) const {
    return new Lambda();
}

/**
 * Simplificar nodo.
 * 
 * Los nodos tipo LAMBDA no pueden simplificarse mas.
 * 
 * @return apuntador a nodo con copia del nodo invocador
 */
Node* Lambda::Simp(void) const {
    return Copy();
}

/**
 * Imprimir el equivalente del nodo invocador en texto crudo.
 * 
 * Imprime el string "lambda".
 * 
 * @param os canal de salida
 * @return canal de salida
*/
ostream& Lambda::Print(ostream& os) const {
    return os << "lambda";
}

/**
 * Generar AFTE.
 * 
 * Funcion recursiva (usada en Node::toAFTE(double,double)) y
 * polimorfica para generar el AFTE correspondiente a la expresion
 * regular del programa en ejecucion. En este caso el AFTE de un nodo de
 * tipo LAMBDA consta de dos nodos unidos por una arista sin rotular,
 * representando una transicion espontanea.
 * 
 * @param x abscisa al origen del punto de referencia del AFTE
 * @param y ordenada al origen del punto de referencia del AFTE
 * 
 * @return AFTE que representa al nodo invocador
 */
AFTE Lambda::toAFTE(double x, double y) {
    AFTE_State* qi = new AFTE_State(x, y);
    AFTE_State* qf = new AFTE_State(x + N + E, y);
    qi->addLambda(qf);
    return AFTE(qi, qf);
}