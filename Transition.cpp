#include "Transition.hpp"

Transition::Transition(string aFrom, string aTo, vector<string> anInput, vector<tapeWM_t> aTapesWM) {
  SetFrom(aFrom);
  SetTo(aTo);
  SetInput(anInput);
  SetTapesIO(aTapesWM);
}

Transition::~Transition() {}

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
  cout << "From State " << GetFrom() << " to state " << GetTo() << ": ((";
  for (int i = 0;i < input.size(); i++) {
    cout << input[i];
    if (i < input.size() - 1)
      cout << ", ";
    else
      cout << "), ";

  }
  for (int i = 0; i < tapesWM.size(); i++) {
    cout << "(" << tapesWM[i].first << ", " << tapesWM[i].second << ")";
    if (i < tapesWM.size() - 1)
      cout << ", ";
    else
      cout << ")" << endl;
  }
}
