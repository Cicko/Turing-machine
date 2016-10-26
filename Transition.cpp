#include "Transition.hpp"

Transition::Transition(string aNext, vector<string> anInput, vector<tapeWM_t> aTapesWM) {
  SetNext(aNext);
  SetInput(anInput);
  SetTapesIO(aTapesWM);
}

~Transition() {}

void Transition::SetNext(string aNext) {
  next = aNext;
}
void Transition::SetInput(vector<string> anInput) {
  input = anInput;
}
void Transition::SetTapesIO(vector<tapeWM_t> aTapesWM) {
  tapesWM = aTapesWM;
}
