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

AFTEL Lambda::toAFTEL(double x, double y) {
    AFTEL_State* qi = new AFTEL_State(x, y);
    cout << "qi: " << qi << endl;
    AFTEL_State* qf = new AFTEL_State(x + N + E, y);
    cout << "qf: " << qf << endl;
    qi->addLambda(qf);
    return AFTEL(qi, qf);
}