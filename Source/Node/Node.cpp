#include "Node.hpp"

Node::~Node() {}

void Node::initDims() {
    height = N;
    width = 2 * N + E;
}

string Node::AfteLatex() {
    initDims();
    string tikz, s, e;
    State qi(0, "initial"), qf(1, "accepting");
    int count = 2;
    AfteLatex(qi, qf, 0, 0, count, s, e);

    tikz += "\\begin{tikzpicture}[initial text = $M$]\n";
    tikz += s;
    tikz += "\\path[->]\n";
    tikz += e;
    tikz += ";\n";
    tikz += "\\end{tikzpicture}\n";

    return tikz;
}

void Node::AfteLatex(State& qi, State& qf, double x, double y, int& count, string& s, string& e) {
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

AFTE Node::toAFTE() {}

AFTEL Node::toAFTEL() {
    this->initDims();
    return this->toAFTEL(0., 0.);
}

AFTEL Node::toAFTEL(double x, double y) {
}

int max(int a, int b) {
    return a > b ? a : b;
}