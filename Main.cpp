/*
Arden's Rule

    lambda\:= {empty word}
    empty:= empty set
    0:= {'0'}
    1:= {'1'}

    a+b:= union of a and b
    a b:= concatenation of a and b
    a*:=  Kleene's closure of a.

    All regular expressions must end with  "."

We want to solve the system:

	E1= a11 E1 + a12 E1 + ... + a1n En + b1
	E2= a21 E1 + a22 E1 + ... + a2n En + b2
        ...
	En= an1 E1 + an2 E1 + ... + ann En + bn

assuming a_ij does not contain lambda.

Input:
     n
     a11.  a12.  ... a1n.  b1.
     a21.  a22.  ... a2n.  b2.
     ...
     an1.  an2.  ... ann.  bn.

Output:
     Solving values for E1,...,En 


Compile this program with g++ on any system
     g++ Arden.cpp -o Arden
Execute:
     ./Arden

				Eduardo Viruena Silva
				November, 2003
*/
#include "RegExpr/RegExp.hpp"
#include "Latex/Latex.hpp"
#include "Misc/State.hpp"

using namespace std;

int main() {
     State q(1.5,2.25,23);
     cout << q.x << endl;
     cout << q.y << endl;
     cout << q.index << endl;
     cout << q.toLatex("accepting,initial");
//     RegExpr exp;
//     cin >> exp;
//     cout << exp.printTree();

    return 0;
}