#include "AFD.hpp"

AFD::AFD(AFTE M) : AFD() {
    unordered_set<AFTE_State*> inputSet = M.RelationE({M.initialState});
    AFD_State* newInitialState = new AFD_State(inputSet);

    this->initialState = newInitialState;

    this->makeTransitions(newInitialState, M);

    int count = 0;
    for (auto& x : this->transitions) {
        x.first->id = count++;
    }
}

void AFD::addState(AFD_State* q, AFTE M) {
    this->states.insert(q);
    if (M.isFinal(*q->AFTE_Equivalent)) {
        this->finalStates.insert(q);
    }
}

void AFD::makeTransitions(AFD_State* q, AFTE M) {
    if (isStateIn(q, this->states)) {
        return;
    }

    this->addState(q, M);

    unordered_set<AFTE_State*> inputSet;
    AFD_State* newState;
    unordered_map<char, AFD_State*> newTransitions;

    for (auto& sigma : this->Sigma) {
        inputSet = M.read(*q->AFTE_Equivalent, sigma);
        newState = new AFD_State(inputSet);
        newState = this->findEquivalent(newState);
        newTransitions.insert({{sigma, newState}});
        this->makeTransitions(newState, M);
    }

    this->transitions.insert({{q, newTransitions}});
}

AFD_State* AFD::findEquivalent(AFD_State* q) {
    for (auto& x : this->states) {
        if (*x->AFTE_Equivalent == *q->AFTE_Equivalent) {
            AFD_State::count--;
            return x;
        }
    }
    return q;
}

string AFD::toString() {
    string s = "{\n";
    s += " states:{ ";
    for (auto& q : this->states) {
        s += "q" + to_string(q->id) + " ";
    }
    s += "},\n";

    s += " initialState: q" + to_string(this->initialState->id) + ",\n";

    s += " finalStates:{ ";
    for (auto& q : this->finalStates) {
        s += "q" + to_string(q->id) + " ";
    }
    s += "},\n";

    s += " transitions:{\n";
    for (auto& transition : this->transitions) {
        s += "\t" + to_string(transition.first->id);
        for (auto& c : transition.second) {
            s += "\t'";
            s += c.first;
            s += "':" + to_string(c.second->id);
        }
        s += "\n";
    }
    s += " }";

    s += "}";
    return s;
}

bool AFD::isFinal(AFD_State* q) {
    for (auto& p : this->finalStates) {
        if (p == q) {
            return true;
        }
    }
    return false;
}

string AFD::toLatexTable() {
    string s;
    s += "\\begin{tabular}{|r||";
    for (auto& x : this->Sigma) {
        s += "c|";
    }
    s += "}\n";
    s += "\t\\hline\n";
    s += "\t $M$";
    for (auto& x : this->Sigma) {
        s += " & $";
        s.push_back(x);
        s += "$";
    }
    s += " \\\\\n";
    s += "\t\\hline\n";
    s += "\t\\hline\n";
    for (auto& t : this->transitions) {
        s += "\t$";

        if (t.first == this->initialState) {
            s += "\\rightarrow{} ";
        }
        if (isFinal(t.first)) {
            s += "*\\;";
        }
        s += "q_{" + to_string(t.first->id) + "}$";

        for (auto& c : this->Sigma) {
            s += " & $q_{" + to_string(t.second[c]->id) + "}$";
        }

        s += " \\\\\n";
        s += "\t\\hline\n";
    }
    s += "\\end{tabular}";
    return s;
}

string AFD::toLatexTableAlpha() {
    string s;
    s += "\\begin{tabular}{|r||";
    for (auto& x : this->Sigma) {
        s += "c|";
    }
    s += "}\n";
    s += "\t\\hline\n";
    s += "\t $M$";
    for (auto& x : this->Sigma) {
        s += " & $";
        s.push_back(x);
        s += "$";
    }
    s += " \\\\\n";
    s += "\t\\hline\n";
    s += "\t\\hline\n";
    for (auto& t : this->transitions) {
        s += "\t$";

        if (t.first == this->initialState) {
            s += "\\rightarrow{} ";
        }
        if (isFinal(t.first)) {
            s += "*\\;";
        }
        s.push_back(char('a' + t.first->id));
        s += "$";

        for (auto& c : this->Sigma) {
            s += " & $";
            s.push_back(char('a' + t.second[c]->id));  // to_string()
            s += "$";
        }

        s += " \\\\\n";
        s += "\t\\hline\n";
    }
    s += "\\end{tabular}";
    return s;
}