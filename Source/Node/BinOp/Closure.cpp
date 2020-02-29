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

AFTE Closure::toAFTE() {
    AFTE_State* q0 = new AFTE_State();
    AFTE_State* q1 = new AFTE_State();
    AFTE M1 = this->left->toAFTE();
    AFTE_State* qf = new AFTE_State();

    q0->addLambda(q1);
    q1->addLambda(M1.initialState);
    q1->addLambda(qf);
    M1.finalState->addLambda(q1);

    return AFTE(q0, qf);
}

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