#include "Letter.hpp"

Letter::Letter(char c) {
    ch = c;
    texStr = "$";
    texStr += c;
    texStr += "$";
}

Letter::~Letter(void) {}

int Letter::Type(void) const {
    return LETTER;
}

Node* Letter::Copy(void) const {
    return new Letter(ch);
}

Node* Letter::Simp(void) const {
    return Copy();
}

ostream& Letter::Print(ostream& os) const {
    return os << ch;
}

void Letter::AfteLatex(State& qi, State& qf, double x, double y, int& count, string& s, string& e) {
    qi.setPos(x, y);
    qf.setPos(x + N + E, y);
    s += qi.toLatex();
    s += qf.toLatex();
    e += qi.toLatex(texStr, qf);
}

AFTE Letter::toAFTE() {
    AFTE_State* q0 = new AFTE_State();
    AFTE_State* qf = new AFTE_State();
    q0->addTransition(this->ch, qf);
    return AFTE(q0, qf);
}