#include "Node.hpp"

Node::~Node() {}

// height y width se utilizan para posicionar los nodos del diagrama 
// de transiciones del AFTE.
// Por defecto N=1 y E=1.
void Node::initDims() {
    height = N;
    width = 2 * N + E;
}

// Esta función sirve para iniciar el proceso de recursividad para obtener
// el codigo Latex del arbol de la expresion. 
string Node::printTree() {
    int k = 0;
    return printTree(k);
}

// Función recursiva para obtener el código Latex del arbol de la expresión.
// Esta definición se utiliza para los nodos 'Empty', 'Lambda' y 'Letter'.
string Node::printTree(int& k) {
    string s;
    tabs(s, k);
    if (k == 0) {
        s += "\\begin{tikzpicture}[nodes={draw, circle}, ->]\n\\";
        // s += "\\";
    }
    s += "node{" + texStr + "}\n";
    if (k == 0) {
        s += ";\n\\end{tikzpicture}\n";
        // s += "\\";
    }
    return s;
}

// Generar 'k' tabulaciones en la cadena 's'.
void tabs(string& s, int k) {
    for (int i = 0; i < k; i++) {
        s += '\t';
    }
}

// Inicializa las dimensiones de los nodos e incia el proceso
// de recursividad para generar el diagrama de transiciones del AFTE
// empezando en la coordenada (0.,0.)
AFTE Node::toAFTE() {
    this->initDims();
    return this->toAFTE(0., 0.);
}

// Funcion recursiva para generar el código Latex del diagrama de
// transiciones del AFTE.
AFTE Node::toAFTE(double x, double y) {
}