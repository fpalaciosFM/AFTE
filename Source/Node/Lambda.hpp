#ifndef LAMBDA_HPP
#define LAMBDA_HPP

#include "Node.hpp"

class Lambda : public Node {
   public:
    Lambda(void);
    virtual ~Lambda(void);
    int Type(void) const;
    Node* Copy(void) const;
    Node* Simp(void) const;
    ostream& Print(ostream& os) const;

    // AFTE Conversion
    AFTE toAFTE(double x, double y);
};

#endif /* LAMBDA_HPP */