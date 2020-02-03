#include "BinOp.hpp"

BinOp::BinOp(Node* l, Node* r) {
    left = l;
    right = r;
}

BinOp::~BinOp(void) {
    if (right != NULL) delete right;
    if (left != NULL) delete left;
}

string BinOp::printTree() {
    int k = 0;
    return printTree(k);
}

string BinOp::printTree(int& k) {
    int n1, n2;
    n1 = n2 = k + 1;
    string s, s1, s2;

    if (left) {
        s1 = left->printTree(n1);
    } else {
        n1--;
    }
    if (right) {
        s2 = right->printTree(n2);
    } else {
        n2--;
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