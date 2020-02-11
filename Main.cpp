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
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "Source/AFD/AFD.hpp"
#include "Source/AFD/AFD_State.hpp"
#include "Source/AFTE/AFTE.hpp"
#include "Source/AFTE/AFTE_State.hpp"
#include "Source/Latex/Latex.hpp"
#include "Source/Misc/State.hpp"
#include "Source/RegExpr/RegExp.hpp"

using namespace std;

int main() {
    // State q(2, "accepting");
    // RegExpr exp;
    // cin >> exp;
    // cout << exp.printTree();
    // cout << "\\\\" << endl;
    // cout << exp.AfteLatex();

    AFTE_State q[5];

    q[0].addLambda(&q[1]);
    q[1].addLambda(&q[2]);
    q[1].addLambda(&q[4]);
    q[2].addTransition('1', &q[3]);
    q[3].addLambda(&q[1]);

    AFTE M(&q[0], &q[4]);

    // cout << M.toString() << endl;

    string s = "11111";
    stringstream* ss = new stringstream(s);

    AFD D(M);

    cout << D.toString() << endl;

    cout << "Todo Bien."
         << endl;

    unordered_set<AFTE_State*> c1 = {&q[0]};
    unordered_set<AFTE_State*> c2 = {&q[0]};
	cout << (c1 == c2) << endl;
    return 0;
}
