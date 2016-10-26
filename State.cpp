#include "State.hpp"

State::State(string anId) {
  id = anId;
  isFinal = false;
}

State::~State() {
	transitions.clear();
	isFinal = false;
}

////// public functions
void State::SetFinal(bool f) {
	isFinal = f;
}

const bool State::IsFinal() {
	return isFinal;
}

int State::GetNumTransitions() {
  return transitions.size();
}

void State::NewTransition(string next, vector<tapeIO_t> tapesIO, string mov) {
  transitions.push_back(new Transition(next, tapesIO, mov));
}

Transition State::GetTransition(int inx) {
		return transitions[inx];
}
