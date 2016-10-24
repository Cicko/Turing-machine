/**
*
* @author: Rudolf Cicko
* @subject: Complejidad computacional (computational complexity), Universidad de La Laguna
* @date: 22-October-2016
* @description: This class represents a state in a Turing machine.
*
**/
#include <cstdlib>

typedef struct {
	char reads;
	char writes;
	char movement;
	int nextState;
} Transition;

class State {
	Transition* transitions;
	int numTransitions;
	bool final;
public:
	State();
	~State();
	void SetFinal(bool f);
	const bool IsFinal();
	const int GetNumTransitions();
	void SetMaxPossibleTrans(int max);  // Set maximum possible transitions
	void NewTransition(char read, char write, char mov, int next);
	const Transition GetTransition(int inx);
};
