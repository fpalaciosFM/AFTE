#include "Closure.hpp"

Closure::Closure(Node* l) : BinOp(l, NULL) {
    texStr = "$*$";
}

Closure::~Closure(void) {
}

void Closure::initDims() {
    left->initDims();
    this->height = left->height + N + E;
    this->width = (3 * N + 2 * E >= left->width) ? (3 * N + 2 * E) : left->width;
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

AFTEL Closure::toAFTEL(double x, double y) {
    AFTEL_State* qi = new AFTEL_State(x, y);
    AFTEL_State* qa = new AFTEL_State(x + (width - N) / 2, y);
    AFTEL M = left->toAFTEL(x + (width - left->width) / 2, y + height - left->height);
    AFTEL_State* qf = new AFTEL_State(x + width - N, y);
    qi->addLambda(qa);
    qa->addLambda(M.initialState);
    M.finalState->addLambda(qa);
    qa->addLambda(qf);
    return AFTEL(qi, qf);
}