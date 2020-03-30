#include <string>
#include <unordered_map>
#include <unordered_set>

#include "Source/AFD/AFD.hpp"
#include "Source/RegExpr/RegExp.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
    RegExpr exp;
    stringstream ss(argv[1]);
    ss >> exp;

    AFTE M = exp.toAFTE();
    AFD A(M);

    // cout << A.toLatexTableAlpha() << endl;

    string input;
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "Tree") == 0) {
            cout << exp.printTree() << endl;
        }
        if (strcmp(argv[i], "AFTE_Diagram") == 0) {
            cout << M.toDiagram() << endl;
        }
        if (strcmp(argv[i], "AFD_Table") == 0) {
            cout << A.toLatexTableAlpha() << endl;
        }
        if (strcmp(argv[i], "Ignore") == 0) {
            input = "exit";
        }
    }

    while (input != "exit" && cin.good()) {
        cerr << "AFTE>> ";
        getline(cin, input);

        if (input == "exit" || cin.eof()) {
            cerr << "Bye!" << endl;
            break;
        }

        ss = stringstream(input);
        cout << M.recognize(&ss) << endl;
    }

    return 0;
}
