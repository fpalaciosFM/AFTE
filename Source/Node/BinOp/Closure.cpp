#include "Closure.hpp"

Closure::Closure(Node* l) : BinOp(l, NULL) {
    texStr = "$*$";
}

Closure::~Closure(void) {
}

void Closure::AfteLatex(State& qi, State& qf, double x, double y, int& count, string& s, string& e) {
    cout << "% Closure :: Hola Mundo" << endl;
    State pi(count++), r(count++), pf(count++);
    qi.setPos(x, y);
    r.setPos(x + (width - N) / 2, y);
    qf.setPos(x + width - N, y);
    s += qi.toLatex();
    s += r.toLatex();
    s += qf.toLatex();
    e += qi.toLatex(r);
    e += r.toLatexClosure(pi, 135, -90);
    e += pf.toLatexClosure(r, -90, 45);
    e += r.toLatex(qf);

    left->AfteLatex(pi, pf, x + (width - left->width) / 2, y + height - left->height, count, s, e);
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