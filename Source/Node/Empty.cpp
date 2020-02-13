#include "Empty.hpp"

Empty::Empty() {
    texStr = "$\\emptyset$";
}

Empty::~Empty(void) {}

void Empty::AfteLatex(State& qi, State& qf, double x, double y, int& count, string& s, string& e) {
    qi.setPos(x, y);
    qf.setPos(x + N + E, y);
    s += qi.toLatex();
    s += qf.toLatex();
}

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

AFTE Empty::toAFTE() {
    AFTE_State* q0 = new AFTE_State();
    AFTE_State* qf = new AFTE_State();
    AFTE M(q0, qf);
    return M;
}