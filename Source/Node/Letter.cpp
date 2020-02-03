#include "Letter.hpp"

Letter::Letter(char c) {
    ch = c;
    texStr = "$";
    texStr += c;
    texStr += "$";
}

Letter::~Letter(void) {}

void Letter::AfteLatex(State& qi, State& qf, double x, double y, int& count, string& s, string& e) {
    qi.setPos(x, y);
    qf.setPos(x + N + E, y);
    s += qi.toLatex();
    s += qf.toLatex();
    e += qi.toLatex(texStr, qf);
}

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