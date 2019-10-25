#ifndef CLOSURE_HPP
#define CLOSURE_HPP

#include "../Lambda.hpp"
#include "BinOp.hpp"

class Closure : public BinOp {
   public:
    Closure(Node* l);
    virtual ~Closure(void);
    virtual int Type(void) const;
    virtual Node* Copy(void) const;
    virtual Node* Simp(void) const;
    virtual ostream& Print(ostream& os) const;

    // AFTE Latex Printing
    virtual void initDims();
};

#endif /* CLOSURE_HPP */