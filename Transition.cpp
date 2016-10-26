#include "Transition.hpp"

Transition::Transition(string aFrom, string aTo, vector<string> anInput, vector<tapeWM_t> aTapesWM) {
  SetFrom(anActual)
  SetTo(aTo);
  SetInput(anInput);
  SetTapesIO(aTapesWM);
}

~Transition() {}

void Transition::SetFrom (string aFrom) {
  from = aFrom;
}

void Transition::SetTo(string aTo) {
  to = aTo;
}
void Transition::SetInput(vector<string> anInput) {
  input = anInput;
}
void Transition::SetTapesIO(vector<tapeWM_t> aTapesWM) {
  tapesWM = aTapesWM;
}

void Transition::ShowTransition () {
  cout << "((" << GetFrom() << ", " << GetTo() << "), ";
  for (int i = 0; i < tapesWM.size(); i++) {
    cout << "(" << aTapesWM[i].first << ", " << aTapesWM[i].second << ")";
    if (i < tapesWM.size() - 1)
      cout << ", ";
    else
      cout << ")" << endl;
  }
}
