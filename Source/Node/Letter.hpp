#ifndef LETTER_HPP
#define LETTER_HPP

#include "Node.hpp"

class Letter : public Node {
   private:
    char ch;

   public:
    Letter(char c);
    virtual ~Letter(void);
    int Type(void) const;
    Node* Copy(void) const;
    Node* Simp(void) const;
    ostream& Print(ostream& os) const;

    // AFTE Conversion
    AFTE toAFTE(double x, double y);
};

#endif /* LETTER_HPP */