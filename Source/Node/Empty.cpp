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

AFTE Empty::toAFTEL(double x, double y) {
    AFTE_State* qi = new AFTE_State(x, y);
    AFTE_State* qf = new AFTE_State(x + N + E, y);
    return AFTE(qi, qf);
}