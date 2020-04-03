#include "Concatenation.hpp"

/**
 * Constructor de nodo Concatenation.
 * 
 * Inicializa el nodo con el string equivalente en Latex.
 */
Concatenation::Concatenation(Node* l, Node* r) : BinOp(l, r) {
    texStr = "$\\cdot$";
}

Concatenation::~Concatenation() {}

/**
 * Inicializa las dimensiones del subdiagrama de transiciones.
 * 
 * La dimension de un nodo es por defecto N = 1.0, y la dimension de
 * una arista (o arco) es E = 1.0. Primero se calculan las dimensiones
 * de los nodos hijos. La altura del nodo invocador es el maximo entre
 * las alturas de nodos hijos. El ancho es la suma de los anchos mas una
 * arista.
 */
void Concatenation::initDims() {
    left->initDims();
    right->initDims();
    this->height = right->height >= left->height ? right->height : left->height;
    this->width = left->width + right->width + E;
}

/**
 * Obtener tipo.
 * 
 * Obtener tipo del nodo invocador.
 *
 * @return enumerador CONCAT
 */
int Concatenation::Type(void) const {
    return CONCAT;
}

/**
 * Obtener copia.
 * 
 * Se crea un nuevo nodo Concatenation con nodo izquiedo apuntando a una
 * copia del hijo izquierdo del nodo invocador, y con nodo derecho 
 * apuntando a una copia del hijo derecho.
 * 
 * @return apuntador a nodo con copia del nodo invocador
 */
Node* Concatenation::Copy(void) const {
    return new Concatenation(left->Copy(), right->Copy());
}

/**
 * Simplificar nodo.
 * 
 * Los nodos tipo CONCAT pueden simplificarse usando las siguientes 2
 * propiedades:
 * 		- El conjunto vacio es elemento neutro para la concatenacion.
 * 		- El conjunto lambda es elemento identidad para la 
 * 		concatenacion.
 * 
 * @return apuntador a nodo con copia del nodo invocador simplificado
 */
Node* Concatenation::Simp(void) const {
    Node* l = left->Simp();
    Node* r = right->Simp();

    int lt = l->Type();
    int rt = r->Type();

    if (lt == EMPTY) {
        delete r;
        return l;
    }

    if (rt == EMPTY) {
        delete l;
        return r;
    }

    if (lt == LAMBDA) {
        delete l;
        return r;
    }

    if (rt == LAMBDA) {
        delete r;
        return l;
    }

    return new Concatenation(l, r);
}

/**
 * Imprimir el equivalente del nodo invocador en texto crudo.
 * 
 * Imprime el texto del nodo hijo izquierdo yuxtapuesto con el texto del
 * nodo hijo derecho. si alguno de los nodos hijos es de tipo UNION,
 * entonces imprime su texto encerrado entre parentesis. 
 * 
 * @param os canal de salida
 * @return canal de salida
 */
ostream& Concatenation::Print(ostream& os) const {
    bool p = left->Type() == UNION;
    if (p)
        os << '(';
    left->Print(os);
    if (p)
        os << ')';

    p = right->Type() == UNION;
    if (p)
        os << '(';
    right->Print(os);
    if (p)
        os << ')';
    return os;
}

/**
 * Generar AFTE.
 * 
 * El AFTE de la concatenacion se obtiene generando el AFTE de los nodos
 * hijos.
 * 		- El estado inicial del AFTE del nodo invocador es el estado
 * 		inicial del AFTE del nodo hijo izquierdo.
 * 		- El estado final del AFTE del nodo invocador es el estado
 * 		final del AFTE del nodo hijo derecho.
 * 		- Se agrega una transicion espontanea desde el estado final del
 * 		AFTE del nodo izquierdo hacia el estado inicial del AFTE del
 * 		nodo derecho.
 * 
 * @return AFTE correspondiente al nodo invocador
 */
AFTE Concatenation::toAFTE(double x, double y) {
    AFTE M1 = left->toAFTE(x, y + (height - left->height) / 2);
    AFTE M2 = right->toAFTE(x + left->width + E, y + (height - right->height) / 2);
    M1.finalState->addLambda(M2.initialState);
    return AFTE(M1.initialState, M2.finalState);
}