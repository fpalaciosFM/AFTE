#ifndef CLOSURE_HPP
#define CLOSURE_HPP

#include "../Lambda.hpp"
#include "BinOp.hpp"

class Closure : public BinOp {
   public:
    Closure(Node* l);
    virtual ~Closure(void);
    int Type(void) const;
    Node* Copy(void) const;
    Node* Simp(void) const;
    ostream& Print(ostream& os) const;

    // AFTE Latex Printing
    void initDims();

    // AFTE Conversion
    AFTE toAFTE(double x, double y);
};

#endif /* CLOSURE_HPP */