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

AFTEL Letter::toAFTEL(double x, double y) {
    AFTEL_State* qi = new AFTEL_State(x, y);
    AFTEL_State* qf = new AFTEL_State(x + N + E, y);
    qi->addTransition(this->ch, qf);
    return AFTEL(qi, qf);
}