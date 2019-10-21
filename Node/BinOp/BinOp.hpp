#ifndef BINOP_HPP
#define BINOP_HPP

#include "../Node.hpp"

class BinOp : public Node {
   protected:
    Node* left;
    Node* right;

   public:
    BinOp(Node* l, Node* r);
    virtual ~BinOp(void);
    virtual int Type(void) const = 0;
    virtual Node* Copy(void) const = 0;
    virtual Node* Simp(void) const = 0;
    virtual ostream& Print(ostream& os) const = 0;
    virtual string printTree();
    virtual string printTree(int&);
};

#endif /* BINOP_HPP */