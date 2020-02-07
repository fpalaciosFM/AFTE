#ifndef AFD_HPP
#define AFD_HPP

#include "AFD_State.hpp"

class AFD {
   public:
    AFD_State* initialState;
    unordered_set<AFD_State*> finalStates;
    unordered_map<AFD_State*, unordered_map<char, AFD_State*>> transitions;

    AFD(){};
    AFD(AFTE M);
    ~AFD(){};
    void addTransition(AFD_State* q, char c, AFD_State* p);
    string toString();

    // AFD_State* read(char c);
    AFD_State* read(stringstream* ss);
    bool recognize(stringstream* ss);
};

#endif /* AFD_HPP */

// AFD_State q1(7, true);
// AFD_State q2(5);

// AFD A;

// cout << q1.id << endl;
// cout << q1.final << endl;
// cout << q2.id << endl;
// cout << q2.final << endl;

// A.addTransition(&q1, '0', &q2);
// A.addTransition(&q1, '1', &q1);
// A.addTransition(&q2, '0', &q1);
// A.addTransition(&q2, '1', &q2);

// cout << A.toString() << endl;

// string s = "00";
// stringstream* ss = new stringstream(s);

// // cout << "A.read(" << s << ") = " << A.read(ss)->id << endl;
// cout << "A.recognize('" << s << "') = " << A.recognize(ss) << endl;