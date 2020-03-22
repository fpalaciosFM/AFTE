#ifndef UNION_HPP
#define UNION_HPP

#include "BinOp.hpp"

class Union : public BinOp {
   public:
    Union(Node* l, Node* r);
    virtual ~Union(void);
    virtual int Type(void) const;
    virtual Node* Copy(void) const;
    virtual Node* Simp(void) const;
    virtual ostream& Print(ostream& os) const;

    // AFTE Latex Printing
    virtual void initDims();

    // AFTEL Conversion
    virtual AFTE toAFTEL(double x, double y);
};

#endif /* UNION_HPP */