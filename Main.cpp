#include <string>
#include <unordered_map>
#include <unordered_set>

#include "Source/AFD/AFD.hpp"
#include "Source/RegExpr/RegExp.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
    RegExpr exp;
    cin >> exp;

    AFTE ML = exp.toAFTE();
    AFD AL(ML);

    cout << AL.toString() << endl;

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "Tree") == 0) {
            cout << exp.printTree() << endl;
        }
        if (strcmp(argv[i], "AFTE_Diagram") == 0) {
            cout << ML.toDiagram() << endl;
        }
        if (strcmp(argv[i], "AFD_Table") == 0) {
            cout << AL.toString() << endl;
        }
    }

    return 0;
}
