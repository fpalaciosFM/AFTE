#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>

#include "../AFTE/AFTE.hpp"
#include "../Misc/Misc.hpp"

using namespace std;

enum {
    LETTER,
    EMPTY,
    LAMBDA,
    UNION,
    CONCAT,
    CLOSURE
};

class Node {
   protected:
    // Tree Latex Printing
    string texStr;

   public:
    virtual ~Node();
    virtual int Type(void) const = 0;
    virtual Node* Copy(void) const = 0;
    virtual Node* Simp(void) const = 0;
    virtual ostream& Print(ostream& os) const = 0;

    // Tree Latex Printing
    string getTexStr() { return texStr; };
    string printTree();
    string printTree(int&);

    // AFTE Latex Printing
    double height;
    double width;
    const double E = 1.0;
    const double N = 1.0;

    virtual void initDims();

    // AFTE Conversion
    AFTE toAFTE();
    virtual AFTE toAFTE(double x, double y) = 0;
};

void tabs(string& s, int k);

#endif /* NODE_HPP */