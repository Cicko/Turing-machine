#include "State.hpp"

State::State() {
  transitions = NULL;
  numTransitions = 0;
  final = false;
}

State::~State() {
	transitions = NULL;
	final = false;
	numTransitions = 0;
}

////// public functions
void State::SetFinal(bool f) {
	final = f;
}

const bool State::IsFinal() {
	return final;
}

const int State::GetNumTransitions() {
	return numTransitions;
}

void State::SetMaxPossibleTrans(int max) {
	if(transitions == NULL)
		transitions = new Transition [max];
}

void State::NewTransition(char rds, char wrt, char mov, int next) {
	transitions[numTransitions].reads = rds;
	transitions[numTransitions].writes = wrt;
	transitions[numTransitions].movement = mov;
	transitions[numTransitions].nextState = next;
  numTransitions++;
}

const Transition State::GetTransition(int inx){
		return transitions[inx];
}
