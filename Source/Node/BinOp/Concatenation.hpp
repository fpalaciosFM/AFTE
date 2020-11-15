#ifndef CONCATENATION_HPP
#define CONCATENATION_HPP

#include "BinOp.hpp"

class Concatenation : public BinOp {
   public:
    Concatenation(Node* l, Node* r);
    virtual ~Concatenation(void);
    int Type(void) const;
    Node* Copy(void) const;
    Node* Simp(void) const;
    ostream& Print(ostream& os) const;

    // AFTE Latex Printing
    void initDims();

    // AFTE Conversion
    AFTE toAFTE(double x, double y);
};

#endif /* CONCATENATION_HPP */