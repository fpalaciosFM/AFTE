#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>

#include "../AFTE_Latex/AFTEL.hpp"
#include "../Latex/Latex.hpp"
#include "../Misc/Misc.hpp"
#include "../Misc/State.hpp"

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
    virtual string printTree();
    virtual string printTree(int&);

    // AFTE Latex Printing
    double height;
    double width;
    const double E = 1.0;
    const double N = 1.0;

    virtual void initDims();
    virtual string AfteLatex();
    virtual void AfteLatex(State& qi, State& qf, double x, double y, int& count, string& s, string& e);

    // AFTEL Conversion
    virtual AFTEL toAFTEL();
    virtual AFTEL toAFTEL(double x, double y);
};

void tabs(string& s, int k);
int max(int a, int b);

#endif /* NODE_HPP */