#include "Lambda.hpp"

Lambda::Lambda(void) {
    texStr = "$\\lambda$";
};

Lambda::~Lambda(void){};

int Lambda::Type(void) const {
    return LAMBDA;
}

Node* Lambda::Copy(void) const {
    return new Lambda();
}

Node* Lambda::Simp(void) const {
    return Copy();
}

ostream& Lambda::Print(ostream& os) const {
    return os << "lambda";
}

void Lambda::AfteLatex(State& qi, State& qf, double x, double y, int& count, string& s, string& e) {
    qi.setPos(x, y);
    qf.setPos(x + N + E, y);
    s += qi.toLatex();
    s += qf.toLatex();
    e += qi.toLatex(qf);
}

AFTE Lambda::toAFTE() {
    AFTE_State* q0 = new AFTE_State();
    AFTE_State* qf = new AFTE_State();
    q0->addLambda(qf);
    return AFTE(q0, qf);
}