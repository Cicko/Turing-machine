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
  string from;                // From state
  string to;                  // To state
  vector<string> input;       // input that reads from n tapes.
  vector<tapeWM_t> tapesWM;   // Write and move on a n tapes.
public:
  Transition(string from, string to, vector<string> input, vector<tapeWM_t> tapesWM);
  ~Transition();

  void SetFrom(string);
  void SetTo(string);
  void SetInput(vector<string> input);
  void SetTapesIO(vector<tapeWM_t> tapesWM);

  string GetFrom () { return from; }
  string GetTo () { return to; }
  vector<string> GetInput () { return input; }
  vector<tapeWM_t> GetTapesWM () { return tapesWM; }

  void ShowTransition ();
};
