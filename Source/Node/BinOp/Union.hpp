#ifndef UNION_HPP
#define UNION_HPP

#include "BinOp.hpp"

class Union : public BinOp {
   public:
    Union(Node* l, Node* r);
    virtual ~Union(void);
    int Type(void) const;
    Node* Copy(void) const;
    Node* Simp(void) const;
    ostream& Print(ostream& os) const;

    // AFTE Latex Printing
    void initDims();

    // AFTE Conversion
    AFTE toAFTE(double x, double y);
};

#endif /* UNION_HPP */