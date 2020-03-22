#ifndef LETTER_HPP
#define LETTER_HPP

#include "Node.hpp"

class Letter : public Node {
   private:
    char ch;

   public:
    Letter(char c);
    virtual ~Letter(void);
    virtual int Type(void) const;
    virtual Node* Copy(void) const;
    virtual Node* Simp(void) const;
    virtual ostream& Print(ostream& os) const;

    // AFTE Conversion
    virtual AFTE toAFTE(double x, double y);
};

#endif /* LETTER_HPP */