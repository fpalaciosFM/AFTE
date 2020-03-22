#ifndef CONCATENATION_HPP
#define CONCATENATION_HPP

#include "BinOp.hpp"

class Concatenation : public BinOp {
   public:
    Concatenation(Node* l, Node* r);
    ~Concatenation(void);
    virtual int Type(void) const;
    virtual Node* Copy(void) const;
    virtual Node* Simp(void) const;
    virtual ostream& Print(ostream& os) const;

    // AFTE Latex Printing
    virtual void initDims();

    // AFTEL Conversion
    virtual AFTEL toAFTEL(double x, double y);
};

#endif /* CONCATENATION_HPP */