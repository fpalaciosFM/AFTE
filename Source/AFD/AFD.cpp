#include "AFD.hpp"

void AFD::addTransition(AFD_State* q, char c, AFD_State* p) {
    unordered_map<char, AFD_State*> map_insert;
    map_insert.insert({c, p});

    if (this->transitions.empty()) {
        this->initialState = q;
    }

    if (q->final) {
        this->finalStates.insert(q);
    }

    if (this->transitions.find(q) == this->transitions.end()) {
        this->transitions.insert({q, map_insert});
    } else {
        if (this->transitions[q].find(c) == this->transitions[q].end()) {
            this->transitions[q].insert({c, p});
        } else {
            this->transitions[q][c] = p;
        }
    }
}

string AFD::toString() {
    string s = "{\n";
    for (auto& elem : this->transitions) {
        for (auto& subelem : elem.second) {
            s += "  f(";
            s += to_string(elem.first->id);
            s += ",\'";
            s += subelem.first;
            s += "\')=";
            s += to_string(subelem.second->id);

            if (this->initialState == elem.first) {
                s += "  State ";
                s += to_string(elem.first->id);
                s += " is initial.";
            }

            if (elem.first->final) {
                s += "  State ";
                s += to_string(elem.first->id);
                s += " is final.";
            }

            s += '\n';
        }
    }
    s += '}';

    return s;
}

AFD_State* AFD::read(stringstream* ss) {
    AFD_State* state_i = this->initialState;
    char c;
    int i = 0;

    while (ss->good() && ss->peek() >= 0) {
        c = ss->get();
        i++;
        state_i = this->transitions[state_i][c];
    }

    return state_i;
}

bool AFD::recognize(stringstream* ss) {
    AFD_State* result = this->read(ss);
    return result->final;
}

void AFD::makeTransitions(AFD_State* q, unordered_set<AFD_State*>* insertedStates, AFTE& M, int& count) {
    if (q->inAFDStateSet(insertedStates)) {
        return;
    }

    unordered_set<AFTE_State*> state0 = M.read(*(q->AFTE_Equivalent), '0');
    unordered_set<AFTE_State*> state1 = M.read(*(q->AFTE_Equivalent), '1');

    AFD_State q0(count++, M.isFinal(state0), &state0);
    AFD_State q1(count++, M.isFinal(state1), &state1);

    insertedStates->insert(q);

    this->makeTransitions(&q0, insertedStates, M, count);
    this->makeTransitions(&q1, insertedStates, M, count);

    this->addTransition(q, '0', &q0);
    this->addTransition(q, '1', &q1);
}

AFD::AFD(AFTE M) {
    int count = 0;
    unordered_set<AFTE_State*> AFTE_initialState = M.initialStates;
    bool initialState_isFinal = M.isFinal(AFTE_initialState);
    this->initialState = new AFD_State(count++, initialState_isFinal, &AFTE_initialState);

    unordered_set<AFTE_State*> state0 = M.read(AFTE_initialState, '0');
    unordered_set<AFTE_State*> state1 = M.read(AFTE_initialState, '1');

    AFD_State q0(count++, M.isFinal(state0), &state0);
    AFD_State q1(count++, M.isFinal(state1), &state1);

    unordered_set<AFD_State*> insertedStates;
    insertedStates.insert(this->initialState);

    this->makeTransitions(&q0, &insertedStates, M, count);
    this->makeTransitions(&q1, &insertedStates, M, count);

    this->addTransition(this->initialState, '0', &q0);
    this->addTransition(this->initialState, '1', &q1);
}