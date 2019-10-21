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