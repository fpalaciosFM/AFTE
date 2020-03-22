#ifndef LAMBDA_HPP
#define LAMBDA_HPP

#include "Node.hpp"

class Lambda : public Node {
   public:
    Lambda(void);
    virtual ~Lambda(void);
    virtual int Type(void) const;
    virtual Node* Copy(void) const;
    virtual Node* Simp(void) const;
    virtual ostream& Print(ostream& os) const;

    // AFTEL Conversion
    virtual AFTE toAFTEL(double x, double y);
};

#endif /* LAMBDA_HPP */