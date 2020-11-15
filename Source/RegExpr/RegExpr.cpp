#include "RegExp.hpp"

RegExpr::RegExpr(Node* e) {
    ptr = e->Simp();
    delete e;
}

RegExpr::RegExpr(void) {
    ptr = new Empty();
}

RegExpr::RegExpr(const RegExpr& e) {
    ptr = e.ptr->Copy();
}

RegExpr::~RegExpr(void) {
    delete ptr;
}

RegExpr& RegExpr::operator=(const RegExpr& e) {
    delete ptr;
    ptr = e.ptr->Copy();
    return *this;
}

ostream& operator<<(ostream& os, const RegExpr& e) {
    return e.ptr->Print(os);
}

istream& operator>>(istream& is, RegExpr& e) {
    Parser P(is);
    e = RegExpr(P.RExp());
    return is;
}

RegExpr operator+(const RegExpr& a, const RegExpr& b) {
    return RegExpr(new Union(a.ptr->Copy(), b.ptr->Copy()));
}

RegExpr operator*(const RegExpr& a, const RegExpr& b) {
    return RegExpr(new Concatenation(a.ptr->Copy(), b.ptr->Copy()));
}

RegExpr operator*(const RegExpr& a) {
    Node* r = new Closure(a.ptr->Copy());
    return RegExpr(r);
}

string RegExpr::printTree() {
    return ptr->printTree();
}

AFTE RegExpr::toAFTE() {
    return ptr->toAFTE();
}