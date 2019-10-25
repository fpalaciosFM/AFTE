#include "Node.hpp"

Node::~Node() {}

void Node::initDims(){
    height = N;
    width = 2*N + E;
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
