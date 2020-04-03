#include "Closure.hpp"

/**
 * Constructor de nodo Closure.
 * 
 * Inicializa el nodo con el string equivalente en Latex.
 */
Closure::Closure(Node* l) : BinOp(l, NULL) {
    texStr = "$*$";
}

Closure::~Closure(void) {
}

/**
 * Inicializa las dimensiones del subdiagrama de transiciones.
 * 
 * La dimension de un nodo es por defecto N = 1.0, y la dimension de
 * una arista (o arco) es E = 1.0. Primero se calculan las dimensiones
 * del nodo hijo izquierdo. La altura de este nodo es un nodo mas una
 * arista mas el alto del subdiagrama del nodo izquierdo. El ancho es el
 * maximo entre 3 nodos mas 2 aristas y el ancho del subdiagrama del
 * nodo izquierdo.
 */
void Closure::initDims() {
    left->initDims();
    this->height = left->height + N + E;
    this->width = (3 * N + 2 * E >= left->width) ? (3 * N + 2 * E) : left->width;
}

/**
 * Obtener tipo.
 * 
 * Obtener tipo del nodo invocador.
 *
 * @return enumerador CLOSURE
 */
int Closure::Type(void) const {
    return CLOSURE;
}

/**
 * Obtener copia.
 * 
 * Se crea un nuevo nodo Closure con nodo izquiedo apuntando a una copia
 * del hijo izquierdo del nodo invocador.
 * 
 * @return apuntador a nodo con copia del nodo invocador
 */
Node* Closure::Copy(void) const {
    return new Closure(left->Copy());
}

/**
 * Simplificar nodo.
 * 
 * Los nodos tipo CLOSURE pueden simplificarse de las siguientes 3
 * formas:
 * 		- la cerradura del conjunto vacio es el conjunto lambda.
 * 		- la cerradora del conjunto lambda es el conjunto lambda.
 * 		- la cerradura es una operacion idempotente.
 * 
 * @return apuntador a nodo con copia del nodo invocador
 */
Node* Closure::Simp(void) const {
    Node* l = left->Simp();
    int tl = l->Type();

    if (tl == EMPTY) {
        delete l;
        return new Lambda();
    }

    if (tl == LAMBDA) {
        delete l;
        return new Lambda();
    }

    if (tl == CLOSURE)
        return l;

    return new Closure(l);
};

/**
 * Imprimir el equivalente del nodo invocador en texto crudo.
 * 
 * Imprime el caracter correspondiente a la letra del nodo invocador.
 * 
 * @param os canal de salida
 * @return canal de salida
 */
ostream& Closure::Print(ostream& os) const {
    int t = left->Type();
    if (t == UNION || t == CONCAT) {
        os << '(';
        left->Print(os);
        os << ')';
    } else
        left->Print(os);
    os << "*";
    return os;
}

/**
 * Generar AFTE.
 * 
 * El AFTE de la cerradura se obtiene generando el AFTE del nodo hijo
 * izquierdo, se generan el estado inicial, el estado final y uno
 * intermedio. 
 * 		- Se agrega una transicion espontanea desde el estado intermedio
 * 		hacia el estado inicial del AFTE del nodo hijo.
 * 		- Se agrega una transicion espontanea desde el estado final del
 * 		AFTE del nodo hijo hacia el estado intermedio.
 * 		- Se agrega una transicion espontanea desde el estado inicial
 * 		hacia el estado intermedio.
 * 		- Se agrega una transicion espontanea desde el estado intermedio
 * 		hacia el estado final.
 * 
 * @return AFTE correspondiente al nodo invocador
 */
AFTE Closure::toAFTE(double x, double y) {
    AFTE_State* qi = new AFTE_State(x, y);
    AFTE_State* qa = new AFTE_State(x + (width - N) / 2, y);
    AFTE M = left->toAFTE(x + (width - left->width) / 2, y + height - left->height);
    AFTE_State* qf = new AFTE_State(x + width - N, y);
    qi->addLambda(qa);
    qa->addLambda(M.initialState);
    M.finalState->addLambda(qa);
    qa->addLambda(qf);
    return AFTE(qi, qf);
}