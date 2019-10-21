#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include "../Latex/Latex.hpp"

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

    //AFTE Latex Printing{
    double Height;
    double Width;
    double x;
    double y;
    const double E = 1.5;
    const double N = 1.0;

   public:
    virtual ~Node();
    virtual int Type(void) const = 0;
    virtual Node* Copy(void) const = 0;
    virtual Node* Simp(void) const = 0;
    virtual ostream& Print(ostream& os) const = 0;

    // Tree Latex Printing
    string getTexStr() { return texStr; };
    virtual string printTree();
    virtual string printTree(int&);

    // AFTE Latex Printing
    // virtual void initDims();
    // virtual string AfteLatex();
    // virtual void setPos(double, double);
};

void tabs(string& s, int k);

#endif /* NODE_HPP */