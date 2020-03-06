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

int main(int argc, char const *argv[]) {
    RegExpr exp;
    cin >> exp;

    AFTEL ML = exp.toAFTEL();
    AFD AF(ML);

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "Tree") == 0) {
            cout << exp.printTree() << endl;
        }
        if (strcmp(argv[i], "AFTE_Diagram") == 0) {
            cout << ML.toDiagram() << endl;
        }
        if (strcmp(argv[i], "AFD_Table")) {
            cout << AF.toString() << endl;
        }
    }

    return 0;
}
