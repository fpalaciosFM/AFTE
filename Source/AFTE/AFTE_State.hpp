#ifndef AFTE_STATE
#define AFTE_STATE

#include <unordered_set>
#include <unordered_map>
#include <sstream>

using namespace std;

class AFTE_State
{
public:
	AFTE_State(bool final);
	~AFTE_State();
	
	unordered_map<char*, unordered_set<AFTE_State*>> transitions;
	bool final;

	unordered_set<AFTE_State*> read(stringstream);
	void addTransition(char* c, AFTE_State* q);

private:
	unordered_set<AFTE_State> read(stringstream, unordered_set<AFTE_State*>);
};

#endif /* AFTE_STATE */