#include "Transition.hpp"

Transition::Transition(string aNext, vector<tapeIO_t> aTapesIO, string aMov) {
  SetNext(aNext);
  SetTapesIO(aTapesIO);
  SetMovement(aMov);
}

~Transition() {}

void Transition::SetNext(string aNext) {
  next = aNext;
}
void Transition::SetTapesIO(vector<tapeIO_t> aTapesIO) {
  tapesIO = aTapesIO;
}
void Transition::SetMovement(string mov) {
  movement = mov;
}
