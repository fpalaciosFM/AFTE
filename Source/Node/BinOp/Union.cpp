#include "Union.hpp"

Union::Union(Node* l, Node* r) : BinOp(l, r) {
    texStr = "$\\cup$";
}

Union::~Union(void) {}

void Union::AfteLatex(State& qi, State& qf, double x, double y, int& count, string& s, string& e) {
    State ai(count++), af(count++), bi(count++), bf(count++);
    qi.setPos(x, y + right->height);
    qf.setPos(x + width - N, y + right->height);
    s += qi.toLatex();
    s += qf.toLatex();
    e += qi.toLatex(ai);
    e += qi.toLatex(bi);
    e += af.toLatex(qf);
    e += bf.toLatex(qf);

    left->AfteLatex(ai, af, x + (width - left->width) / 2, y + right->height + N, count, s, e);
    right->AfteLatex(bi, bf, x + (width - right->width) / 2, y, count, s, e);
}

void Union::initDims() {
    left->initDims();
    right->initDims();
    this->height = left->height + right->height + N;
    this->width = 2 * N + 2 * E + max(left->width, right->width);
}

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