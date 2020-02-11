#include "AFD.hpp"

AFD::AFD(AFTE M) : AFD() {
    unordered_set<AFTE_State*> inputSet = M.RelationE({M.initialState});
    AFD_State* newInitialState = new AFD_State(inputSet);
    this->initialState = newInitialState;

    this->states.insert(newInitialState);
    AFD_State* newState;

    this->addTransitions(newState, M);
    // for (auto& sigma : this->Sigma) {
    //     inputSet = M.read(*this->initialState->AFTE_Equivalent, sigma);
    //     newState = new AFD_State(inputSet);
    // }
}

string AFD::toString() {
    string s = "{\n";
    s += " initialState: q" + to_string(this->initialState->id) + ",\n";
    // s += " finalState: q" + to_string(this->finalState->id) + ",\n";
    s += " states:{ ";
    for (auto& q : this->states) {
        s += "q" + to_string(q->id) + " ";
    }
    s += "}\n";
    return s;
}

void AFD::addTransitions(AFD_State* q, AFTE M) {
    if (isStateIn(q, this->states)) {
        return;
    }

    unordered_set<AFTE_State*> inputSet;
    AFD_State* newState;
    unordered_map<char, AFD_State*> newTransition;

    for (auto& sigma : this->Sigma) {
        cout << endl
             << "iterando para " << sigma << endl;
        inputSet = M.read(*this->initialState->AFTE_Equivalent, sigma);
        newState = new AFD_State(inputSet);
        newState = this->findEquivalent(newState);
        this->states.insert(newState);
        newTransition.insert({{sigma, newState}});
        cout << "new id:" << to_string(newState->id) << endl;
    }

    // AFD_State* aux_q = getStateFrom(q, this->states);
    // q = aux_q ? aux_q : q;
}

AFD_State* AFD::findEquivalent(AFD_State* q) {
    bool flag = false;
    for (auto& x : this->states) {
        if (*x->AFTE_Equivalent == *q->AFTE_Equivalent) {
            return x;
        }
    }
    return q;
}
