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

AFTE Letter::toAFTE(double x, double y) {
    AFTE_State* qi = new AFTE_State(x, y);
    AFTE_State* qf = new AFTE_State(x + N + E, y);
    qi->addTransition(this->ch, qf);
    return AFTE(qi, qf);
}