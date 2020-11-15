#ifndef EMPTY_HPP
#define EMPTY_HPP

#include "Node.hpp"

class Empty : public Node {
   public:
    Empty(void);
    virtual ~Empty(void);
    int Type(void) const;
    Node* Copy(void) const;
    Node* Simp(void) const;
    ostream& Print(ostream& os) const;

    // AFTE Conversion
    AFTE toAFTE(double x, double y);
};

#endif /* EMPTY_HPP */