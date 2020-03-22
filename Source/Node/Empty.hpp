#ifndef EMPTY_HPP
#define EMPTY_HPP

#include "Node.hpp"

class Empty : public Node {
   public:
    Empty(void);
    virtual ~Empty(void);
    virtual int Type(void) const;
    virtual Node* Copy(void) const;
    virtual Node* Simp(void) const;
    virtual ostream& Print(ostream& os) const;

    //AFTE Latex Printing
    virtual void AfteLatex(State& qi, State& qf, double x, double y, int& count, string& s, string& e);

    // AFTEL Conversion
    virtual AFTEL toAFTEL(double x, double y);
};

#endif /* EMPTY_HPP */