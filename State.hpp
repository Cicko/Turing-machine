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
#include "Utils.hpp"
#include "Transition.hpp"
#include "tapeWM_t.hpp"

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
	void NewTransition (string transition, int numTapes);
	Transition* GetTransition(int inx);
	void ShowAllTransitions ();
private:
	void NewTransition(string to, vector<string> input, vector<tapeWM_t> aTapesWM);
};
