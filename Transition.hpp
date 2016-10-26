/**
*
* @author: Rudolf Cicko
* @subject: Complejidad computacional (computational complexity), Universidad de La Laguna
* @date: 26-October-2016
* @description: This class represents a transition in a Turing Machine. It allows multitape machine (with n independent head movements)
*
**/
#include <vector>
#include <string>
#include <iostream>
#include "tapeWM_t.hpp"

using namespace std;


class Transition {
  string next;                // Next state
  vector<string> input;       // input that reads from n tapes.
  vector<tapeWM_t> tapesWM;   // Write and move on a n tapes.
public:
  Transition(string next, vector<string> input, vector<tapeWM_t> tapesWM);
  ~Transition();

  void SetNext(string);
  void SetInput(vector<string> input);
  void SetTapesIO(vector<tapeWM_t> tapesIO);

  string GetNext () { return next; }
  vector<string> GetInput () { return input; }
  vector<tapeWM_t> GetTapesIO () { return tapesWM; }
}
