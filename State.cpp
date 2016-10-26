#include "State.hpp"

void State::NewTransition(string to, vector<string> input, vector<tapeWM_t> tapesWM) {
  transitions.push_back(new Transition(GetId(), to, input, tapesWM));
}

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

void State::NewTransition (string transition, int numTapes) {
  vector<string> trans = utils::lineToStrings(transition, " ");
  int inx = 1;  // Index of the word in the complete transition.
  string nextState;
  vector<string> input;
  vector<string> writes;
  vector<string> movements;
  vector<tapeWM_t> tapesWM;

  // Read input
  for (int i = 0; i < numTapes; i++) {
    input.push_back(trans[inx++]);
  }

  // Read next state
  nextState = trans[inx++];

  // Read writes
  for (int i = 0; i < numTapes; i++) {
    writes.push_back(trans[inx++]);
  }

  // Read movements
  for (int i = 0; i < numTapes; i++) {
    movements.push_back(trans[inx++]);
  }

  // Construct tape Write-Move structure data for every tape and push it to the set of them.
  for (int i = 0; i < numTapes; i++) {
    tapeWM_t oneTapeWM;
    oneTapeWM.first = writes[i];
    oneTapeWM.second = movements[i];
    tapesWM.push_back(oneTapeWM);
  }

  // Construct the transition.
  NewTransition(nextState, input, tapesWM);
}



Transition* State::GetTransition(int inx) {
		return transitions[inx];
}



void State::ShowAllTransitions () {
    for (int i = 0; i < GetNumTransitions(); i++) {
      transitions[i]->ShowTransition();
    }
}
