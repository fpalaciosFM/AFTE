#include "Union.hpp"

/**
 * Constructor de nodo Concatenation.
 * 
 * Inicializa el nodo con el string equivalente en Latex (union).
 */
Union::Union(Node* l, Node* r) : BinOp(l, r) {
    texStr = "$\\cup$";
}

Union::~Union(void) {}

/**
 * Inicializa las dimensiones del subdiagrama de transiciones.
 * 
 * La dimension de un nodo es por defecto N = 1.0, y la dimension de
 * una arista (o arco) es E = 1.0. Primero se calculan las dimensiones
 * de los nodos hijos. La altura del nodo invocador es la suma de las
 * alturas mas un nodo. El ancho es el maximo de los anchos de los nodos
 * hijos mas 2 nodos mas 2 aristas.
 */
void Union::initDims() {
    left->initDims();
    right->initDims();
    this->height = left->height + right->height + N;
    this->width = 2 * N + 2 * E + max(left->width, right->width);
}

/**
 * Obtener tipo.
 * 
 * Obtener tipo del nodo invocador.
 *
 * @return enumerador UNION
 */
int Union::Type(void) const {
    return UNION;
}

/**
 * Obtener copia.
 * 
 * Se crea un nuevo nodo Union con nodo izquiedo apuntando a una
 * copia del hijo izquierdo del nodo invocador, y con nodo derecho 
 * apuntando a una copia del hijo derecho.
 * 
 * @return apuntador a nodo con copia del nodo invocador
 */
Node* Union::Copy(void) const {
    return new Union(left->Copy(), right->Copy());
}

/**
 * Simplificar nodo.
 * 
 * Los nodos tipo UNION pueden simplificarse usando las siguientes 2
 * propiedades:
 * 		- El conjunto vacio es elemento identidad para la concatenacion.
 * 		- El conjunto lambda es subconjunto de la cerradura de cualquier
 * 		conjunto.
 * 
 * @return apuntador a nodo con copia del nodo invocador simplificado
 */
Node* Union::Simp(void) const {
    Node* l = left->Simp();
    Node* r = right->Simp();

    int lt = l->Type();
    int rt = r->Type();

    if (lt == EMPTY) {
        delete l;
        return r;
    }
    if (rt == EMPTY) {
        delete r;
        return l;
    }

    if (lt == CLOSURE && rt == LAMBDA) {
        delete r;
        return l;
    }
    if (rt == CLOSURE && lt == LAMBDA) {
        delete l;
        return r;
    }

    return new Union(l, r);
}

/**
 * Imprimir el equivalente del nodo invocador en texto crudo.
 * 
 * Imprime el texto del nodo hijo izquierdo, un signo + y el texto del
 * nodo hijo derecho.
 * 
 * @param os canal de salida
 * @return canal de salida
 */
ostream& Union::Print(ostream& os) const {
    left->Print(os);
    os << " + ";
    right->Print(os);
    return os;
}

/**
 * Generar AFTE.
 * 
 * El AFTE de la union se obtiene generando el AFTE de los nodos
 * hijos, se generan dos nodos, el estado inicial y el estado final del
 * AFTE del nodo invocador.
 * 		- Se agraga una transicion espontanea desde el estado inicial 
 * 		del nodo invocador hacia el estado inicial del AFTE del nodo
 * 		hijo izquierdo.
 * 		- Se agraga una transicion espontanea desde el estado inicial 
 * 		del nodo invocador hacia el estado inicial del AFTE del nodo
 * 		hijo derecho.
 * 		- Se agrega una transicion espontanea desde el estado final del
 * 		AFTE del nodo hijo izquierdo hacia el estado final del AFTE del
 * 		nodo invocador.
 * 		- Se agrega una transicion espontanea desde el estado final del
 * 		AFTE del nodo hijo derecho hacia el estado final del AFTE del
 * 		nodo invocador.
 * 
 * @return AFTE correspondiente al nodo invocador
 */
AFTE Union::toAFTE(double x, double y) {
    AFTE_State* qi = new AFTE_State(x, y + left->height);
    AFTE M1 = left->toAFTE(x + (width - left->width) / 2, y);
    AFTE M2 = right->toAFTE(x + (width - right->width) / 2, y + left->height + N);
    AFTE_State* qf = new AFTE_State(x + width - N, y + left->height);
    qi->addLambda(M1.initialState);
    qi->addLambda(M2.initialState);
    M1.finalState->addLambda(qf);
    M2.finalState->addLambda(qf);
    return AFTE(qi, qf);
}