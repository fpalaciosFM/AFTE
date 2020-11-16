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
    string printTree();
    AFTE toAFTE();
};

void PrintMat(RegExpr** A, int N);
void Arden(RegExpr** A, int N);

#endif /* REGEXPR_HPP */