#ifndef REGEXPR_HPP
#define REGEXPR_HPP

#include "Parser.hpp"

class RegExpr {
   private:
    Node* ptr;
    RegExpr(Node*);

   public:
    RegExpr(void);
    RegExpr(const RegExpr&);
    ~RegExpr();
    RegExpr& operator=(const RegExpr& e);
    friend ostream& operator<<(ostream& os, const RegExpr& e);
    friend istream& operator>>(istream& is, RegExpr& e);
    friend RegExpr operator+(const RegExpr& a, const RegExpr& b);
    friend RegExpr operator*(const RegExpr& a, const RegExpr& b);
    friend RegExpr operator*(const RegExpr& a);
    string printTree();
    AFTEL toAFTEL();
};

void PrintMat(RegExpr** A, int N);
void Arden(RegExpr** A, int N);

#endif /* REGEXPR_HPP */