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
    AFTE_State state3(3);
    AFTE_State state4(4);
    AFTE_State state5(5);
    AFTE_State state6(6, true);

    string s = "101010";
    stringstream* ss = new stringstream(s);

    state1.addLambda(&state2);
    state2.addLambda(&state3);
    state2.addLambda(&state6);
    state3.addTransition('1', &state4);
    state4.addTransition('0', &state5);
    state5.addLambda(&state2);

    unordered_set<AFTE_State*> conjunto = {&state1};

    unordered_set<AFTE_State*> conjuntoEK = conjunto;
    while (ss->good()) {
        char c = ss->get();

        if (c > 0) {
            cout << endl;
            unordered_set<AFTE_State*> conjuntoEi;
            unordered_set<AFTE_State*> conjuntoEii = conjunto;
            int oldLength;

            do {
                conjuntoEi = conjuntoEii;
                conjuntoEii = unordered_set<AFTE_State*>();
                oldLength = conjuntoEK.size();
				cout << c << endl;
                cout << "oldLength = " << oldLength << endl;

                //
                cout << "Ei = { ";
                for (auto& state : conjuntoEi) {
                    cout << state->id << ' ';
                }
                cout << '}' << endl;

                cout << "Eii = { ";
                for (auto& state : conjuntoEii) {
                    cout << state->id << ' ';
                }
                cout << '}' << endl;

                cout << "EK = { ";
                for (auto& state : conjuntoEK) {
                    cout << state->id << ' ';
                }
                cout << '}' << endl;
				//

                for (auto& state : conjuntoEi) {
                    for (auto& q : state->lambdas) {
                        conjuntoEii.insert(q);
                    }
                }

                for (auto& state : conjuntoEii) {
                    conjuntoEK.insert(state);
                }
                cout << "newLength = " << conjuntoEK.size() << endl;

                // conjuntoEK.merge(conjuntoEii);
            } while (conjuntoEK.size() != oldLength);
        }
    }

    // state.read(char(ss->get()));

    printf("Todo Bien.\n");

    return 0;
}