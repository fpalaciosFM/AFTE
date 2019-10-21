#include "Closure.hpp"

Closure::Closure(Node* l) : BinOp(l, NULL) {
    texStr = "$*$";
}

Closure::~Closure(void) {
}

int Closure::Type(void) const {
    return CLOSURE;
}

Node* Closure::Copy(void) const {
    return new Closure(left->Copy());
}

ostream& Closure::Print(ostream& os) const {
    int t = left->Type();
    if (t == UNION || t == CONCAT) {
        os << '(';
        left->Print(os);
        os << ')';
    } else
        left->Print(os);
    os << "*";
    return os;
}

Node* Closure::Simp(void) const {
    Node* l = left->Simp();
    int tl = l->Type();

    if (tl == EMPTY) {
        delete l;
        return new Lambda();
    }

    if (tl == LAMBDA) {
        delete l;
        return new Lambda();
    }

    if (tl == CLOSURE)
        return l;

    return new Closure(l);
};