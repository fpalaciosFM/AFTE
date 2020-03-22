#include "Concatenation.hpp"

Concatenation::Concatenation(Node* l, Node* r) : BinOp(l, r) {
    texStr = "$\\cdot$";
}

Concatenation::~Concatenation() {}

void Concatenation::initDims() {
    left->initDims();
    right->initDims();
    this->height = right->height >= left->height ? right->height : left->height;
    this->width = left->width + right->width + E;
}

int Concatenation::Type(void) const {
    return CONCAT;
}

Node* Concatenation::Copy(void) const {
    return new Concatenation(left->Copy(), right->Copy());
}

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

AFTE Concatenation::toAFTEL(double x, double y) {
    AFTE M1 = left->toAFTEL(x, y + (height - left->height) / 2);
    AFTE M2 = right->toAFTEL(x + left->width + E, y + (height - right->height) / 2);
    M1.finalState->addLambda(M2.initialState);
    return AFTE(M1.initialState, M2.finalState);
}