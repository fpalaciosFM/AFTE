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

AFTEL Lambda::toAFTEL(double x, double y) {
    AFTEL_State* qi = new AFTEL_State(x, y);
    cout << "qi: " << qi << endl;
    AFTEL_State* qf = new AFTEL_State(x + N + E, y);
    cout << "qf: " << qf << endl;
    qi->addLambda(qf);
    return AFTEL(qi, qf);
}