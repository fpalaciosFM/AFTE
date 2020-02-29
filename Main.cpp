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
    // AFTE_State q[5];

    // q[0].addLambda(&q[1]);
    // q[1].addLambda(&q[2]);
    // q[1].addLambda(&q[4]);
    // q[2].addTransition('1', &q[3]);
    // q[3].addLambda(&q[1]);

    // AFTE M(&q[0], &q[4]);

    // // cout << M.toString() << endl;

    // string s = "11111";
    // stringstream* ss = new stringstream(s);

    // AFD D(M);

    // cout << D.toString() << endl
    //      << endl;

    RegExpr exp;
    cout << "Ingrese una expresion regular: ";
    cin >> exp;
    // cout << exp.printTree();
    // cout << "\\\\" << endl;
    // cout << exp.AfteLatex();
    // AFTE M = exp.toAFTE();
    // cout << "Initial State: " << M.initialState->id << endl;
    // cout << "Final State: " << M.finalState->id << endl;
    // cout << M.toString() << endl;

    // cout << endl
    //      << exp.AfteLatex() << endl;

    // cout << endl
    //      << "Todo Bien."
    //      << endl
    //      << endl;

    AFTEL ML = exp.toAFTEL();

    cout << endl
         << "AFTEL:" << endl;
    cout << "Initial State: " << ML.initialState->id << endl;
    cout << "Final State: " << ML.finalState->id << endl;
    cout << ML.toDiagram() << endl;
    cout << exp.printTree() << endl;

    cout << endl
         << "Todo Bien."
         << endl
         << endl;

    return 0;
}
