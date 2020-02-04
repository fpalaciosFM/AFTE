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

    AFTE_State state1(1);
    AFTE_State state2(2);

    string s = "101010";
    stringstream* ss = new stringstream(s);

    state1.addTransition('1', &state2);
    state1.addTransition('0', &state1);
    state2.addTransition('0', &state1);
    state2.addTransition('0', &state2);

	state1.print(cout) << endl;
	state2.print(cout) << endl;

    // state.read(char(ss->get()));

    printf("Todo Bien.\n");

    return 0;
}