#include "AFD.hpp"

AFD::AFD(AFTEL M) : AFD() {
    unordered_set<AFTEL_State*> inputSet = M.RelationE({M.initialState});
    AFD_State* newInitialState = new AFD_State(inputSet);

    this->initialState = newInitialState;

    this->makeTransitions(newInitialState, M);

    int count = 0;
    for (auto& x : this->transitions) {
        x.first->id = count++;
    }
}

void AFD::addState(AFD_State* q, AFTEL M) {
    this->states.insert(q);
    if (M.isFinal(*q->AFTEL_Equivalent)) {
        this->finalStates.insert(q);
    }
}

void AFD::makeTransitions(AFD_State* q, AFTEL M) {
    if (isStateIn(q, this->states)) {
        return;
    }

    this->addState(q, M);

    unordered_set<AFTEL_State*> inputSet;
    AFD_State* newState;
    unordered_map<char, AFD_State*> newTransitions;

    for (auto& sigma : this->Sigma) {
        inputSet = M.read(*q->AFTEL_Equivalent, sigma);
        newState = new AFD_State(inputSet);
        newState = this->findEquivalentL(newState);
        newTransitions.insert({{sigma, newState}});
        this->makeTransitions(newState, M);
    }

    this->transitions.insert({{q, newTransitions}});
}

AFD_State* AFD::findEquivalentL(AFD_State* q) {
    for (auto& x : this->states) {
        if (*x->AFTEL_Equivalent == *q->AFTEL_Equivalent) {
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
