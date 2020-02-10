#ifndef AFD_STATE_HPP
#define AFD_STATE_HPP

#include "../AFTE/AFTE.hpp"

class AFD_State {
   public:
    int id;
    bool final;
    unordered_set<AFTE_State*> AFTE_Equivalent;

    AFD_State(int id);
    AFD_State(int id, bool final) : AFD_State(id) { this->final = final; };
    ~AFD_State(){};
};

#endif /* AFD_STATE_HPP */

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
// cout << "A.recognize(" << s << ") = " << A.recognize(ss) << endl;

// printf("Todo Bien.\n");