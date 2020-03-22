#include "Empty.hpp"

Empty::Empty() {
    texStr = "$\\emptyset$";
}

Empty::~Empty(void) {}

int Empty::Type(void) const {
    return EMPTY;
}

Node* Empty::Copy(void) const {
    return new Empty();
}

Node* Empty::Simp(void) const {
    return Copy();
}

ostream& Empty::Print(ostream& os) const {
    return os << "empty";
}

AFTEL Empty::toAFTEL(double x, double y) {
    AFTEL_State* qi = new AFTEL_State(x, y);
    AFTEL_State* qf = new AFTEL_State(x + N + E, y);
    return AFTEL(qi, qf);
}