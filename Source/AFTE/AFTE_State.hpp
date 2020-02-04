#ifndef AFTE_STATE
#define AFTE_STATE

#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class AFTE_State {
   public:
    static int* count;
    unordered_map<char, unordered_set<AFTE_State*>> transitions;
    unordered_set<AFTE_State*> lambdas;
    bool final;
    int id;

    AFTE_State(int id);
    AFTE_State(int id, bool final) : AFTE_State(id) { this->final = final; };
    ~AFTE_State();

    unordered_set<AFTE_State*> read(char);
    void addTransition(char c, AFTE_State* q);
    void addLambda(AFTE_State* q);
    ostream& print(ostream& os);
};

#endif /* AFTE_STATE */