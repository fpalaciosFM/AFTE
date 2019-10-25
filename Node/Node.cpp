#include "Node.hpp"

Node::~Node() {}

void Node::initDims() {
    height = N;
    width = 2 * N + E;
}

string Node::AfteLatex() {
    initDims();
    string tikz, s, e;
    State qi(0), qf(1);
    int count = 2;
    AfteLatex(qi, qf, 0, 0, count, s, e);
    s += qi.toLatex();
    s += qf.toLatex();

    tikz += "\\begin{tikzsfigure}[initial text = \"$M$\"]\n";
    tikz += s;
    tikz += "\\path[->]\n";
    tikz += e;
    tikz += ";\n";
    tikz += "\\end{tikzpicture}\n";

    return tikz;
}

string Node::printTree() {
    int k = 0;
    return printTree(k);
}

string Node::printTree(int& k) {
    string s;
    tabs(s, k);
    if (k == 0) {
        s += "\\";
    }
    s += "node{" + texStr + "}\n";
    return s;
}

void tabs(string& s, int k) {
    for (int i = 0; i < k; i++) {
        s += '\t';
    }
}
