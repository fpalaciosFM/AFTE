#include "Union.hpp"

Union::Union(Node* l, Node* r) : BinOp(l, r) {
    texStr = "$\\cup$";
}

Union::~Union(void) {}

int Union::Type(void) const {
    return UNION;
}

Node* Union::Copy(void) const {
    return new Union(left->Copy(), right->Copy());
}

ostream& Union::Print(ostream& os) const {
    left->Print(os);
    os << " + ";
    right->Print(os);
    return os;
}

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

void Union::initDims() {
    left->initDims();
    right->initDims();
    this->height = left->height + right->height + N;
    this->width = 2 * N + 2 * E + max(left->width, right->width);
}

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