/**
*
* @author: Rudolf Cicko
* @subject: Complejidad computacional (computational complexity), Universidad de La Laguna
* @date: 22-October-2016
* @description: This class represents a state in a Turing machine.
*
**/
#include <cstdlib>
#include <string>
#include <vector>
#include "Transition.hpp"
#include "tapeIO_t.hpp"

using namespace std;


class State {
	string id;  // Identifier for the state. For example: q1, q2, q3, ....qn
	vector<Transition*> transitions;
	bool isFinal;
public:
	State(string id);
	~State();
	void SetFinal(bool f);
	const bool IsFinal();
	string GetId() { return id; };
	int GetNumTransitions();
	void NewTransition(string aNext, vector<tapeIO_t> aTapesIO, string aMov);
	Transition GetTransition(int inx);
	/*
	inline bool operator< (const State& lhs, const State& rhs){ return lhs.GetId() < rhs.GetId(); }
	inline bool operator> (const State& lhs, const State& rhs){ return rhs < lhs; }
	inline bool operator<=(const State& lhs, const State& rhs){ return !(lhs > rhs); }
	inline bool operator>=(const State& lhs, const State& rhs){ return !(lhs < rhs); }
	*/
};
