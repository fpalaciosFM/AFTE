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

AFTE Lambda::toAFTEL(double x, double y) {
    AFTE_State* qi = new AFTE_State(x, y);
    cout << "qi: " << qi << endl;
    AFTE_State* qf = new AFTE_State(x + N + E, y);
    cout << "qf: " << qf << endl;
    qi->addLambda(qf);
    return AFTE(qi, qf);
}