#include "Node.hpp"

Node::~Node() {}

/**
 * Inicializa las dimensiones del subdiagrama de transiciones.
 * 
 * La dimension de un nodo es por defecto N = 1.0, y la dimension de
 * una arista (o arco) es E = 1.0. Esta definicion es la misma que se
 * utiliza para los nodos 'Empty', 'Lambda' y 'Letter'. Las
 * dimensiones de los diagramas de estos tres nodos es la misma y es
 * igual a 1 de alto (1 nodo de alto) por 3 de ancho (2 nodos mas 1
 * arista de ancho).
 */
void Node::initDims() {
    height = N;
    width = 2 * N + E;
}

/**
 * Inicializa recursividad para el arbol de expresion.
 * 
 * Esta función sirve para iniciar el proceso de recursividad para
 * obtener el codigo Latex del arbol de la expresion. 
 * 
 * @return string con el codigo latex correspondiente al arbol de la
 * 		expresion
 */
string Node::printTree() {
    int k = 0;
    return printTree(k);
}

/**
 * Generacion recursiva de arbol de expresion.
 * 
 * Generacion de codigo Latex del arbol de expresion. En el caso k=0
 * se inicializa la cadena a retornar. Esta definicion es el caso
 * base y se utiliza para los nodos 'Empty', 'Lambda' y 'Letter'.
 * 
 * @param k es el numero de tabulaciones a insertar en la cadena.
 * 		Solamente se usa con fines esteticos
 * @return string con el codigo latex correspondiente al arbol de la
 * 		expresion
 */
string Node::printTree(int& k) {
    string s;
    tabs(s, k);
    if (k == 0) {
        s += "\\begin{tikzpicture}[nodes={draw, circle}, ->]\n\\";
    }
    s += "node{" + texStr + "}\n";
    if (k == 0) {
        s += ";\n\\end{tikzpicture}\n";
    }
    return s;
}

/**
 * Generador de tabulaciones.
 * 
 * Genera tabulaciones en un string.
 * 
 * @param[out] s string al que se le agregaran tabulaciones
 * @param[in] k numero de tabulaciones a agregar
 */
void tabs(string& s, int k) {
    for (int i = 0; i < k; i++) {
        s += '\t';
    }
}

/**
 * Generador del AFTE correspondiente a la expresion regular del 
 * programa.
 * 
 * Inicializa las dimensiones de los nodos e incia el proceso de
 * recursividad para generar el AFTE e inicializar los parametros
 * necesarios para generar su diagrama de transiciones empezando en
 * la coordenada (0.,0.).
 * 
 * @return AFTE correspondiente a la expresión regular del programa
 * 		en ejecucion
 */
AFTE Node::toAFTE() {
    this->initDims();
    return this->toAFTE(0., 0.);
}

// /**
//  * Recursividad para generar el AFTE y los parametros para generar el
//  * codigo Latex de su diagrama de transiciones.
//  * 
//  * Una vez que las dimensiones se encuentren inicializadas se procede
//  * a generar los subdiagramas de transiciones de los nodos hijos y
//  * despues se ensamblan dependiendo del tipo de nodo padre. si no se
//  * tienen nodos hijos simplemente se regresa el AFTE correspondiente
//  * al nodo padre.
//  * 
//  * @return AFTE correspondiente a la expresión regular del programa
//  * 		en ejecucion
// */
// AFTE Node::toAFTE(double x, double y) {
// }