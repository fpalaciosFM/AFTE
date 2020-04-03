#include "BinOp.hpp"

/**
 * Constructor de nodo binario.
 * 
 * Los nodos binarios represnetan las operaciones binarias, constan de
 * dos apuntadores a nodo (nodos hijos) que representan los respectivos
 * operandos del operador (nodo padre).
 * 
 * @param l nodo izquierdo (left)
 * @param r nodo derecho (right)
 */
BinOp::BinOp(Node* l, Node* r) {
    left = l;
    right = r;
}

/**
 * 
 */
BinOp::~BinOp(void) {
    if (right != NULL) delete right;
    if (left != NULL) delete left;
}

/**
 * Inicializacion de recursividad para obtencion del arbol de la
 * expresion.
 * 
 * @return string del codigo Latex del arbol de la expresion
 */
string BinOp::printTree() {
    int k = 0;
    return printTree(k);
}

/**
 * Obtener el arbol de la expresion usando recursividad.
 * 
 * El arbol se obtiene invocando esta funcion en los nodos hijos y
 * despues el nodo invocador ensambla los string obtenidos. El parametro
 * sirve para identificar el nivel del arbol del que se esta generando
 * el codigo Latex. Los nodos se disponen considerando el peor de los
 * casos, donde el nivel 'b' tiene 2^b nodos, suponiendo que la raiz se
 * cuenta como el nivel 0 del arbol.
 * 
 * @param[out] k nivel del arbol que se esta generando
 */
string BinOp::printTree(int& k) {
    int n1, n2;
    n1 = n2 = k;
    string s, s1, s2;

    if (left) {
        s1 = left->printTree(++n1);
    }
    if (right) {
        s2 = right->printTree(++n2);
    }

    int m = n1 >= n2 ? n1 : n2;

    tabs(s, k);
    if (k == 0) {
        s += "\\begin{tikzpicture}[nodes={draw, circle}, ->]\n\\";
    }
    s += "node{";
    s += texStr;
    s += "}\n";

    if (left) {
        tabs(s, k);
        s += "child{\n";
        s += s1;
        tabs(s, k);
        s += "}\n";
    } else {
        n1 = k;
    }

    int b = 1;
    for (int i = 0; i < m - k - 1; i++) {
        for (int j = 0; j < b; j++) {
            tabs(s, k);
            s += "child[missing]\n";
        }
        b *= 2;
    }

    if (right) {
        tabs(s, k);
        s += "child{\n";
        s += s2;
        tabs(s, k);
        s += "}\n";
    } else {
        n2 = k;
    }

    if (k == 0) {
        s += ";\n\\end{tikzpicture}\n";
    }

    k = m;
    return s;
}