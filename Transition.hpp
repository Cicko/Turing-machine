
#include <vector>
#include <string>
#include <iostream>
#include "tapeIO_t.hpp"

using namespace std;



class Transition {
  string next;                // Next state
  vector<tapeIO_t> tapesIO;   // Read and write for all tapes.
  string movement;
public:
  Transition(string next, vector<tapeIO_t> tapesIO, string mov);
  ~Transition();

  void SetNext(string);
  void SetTapesIO(vector<tapeIO_t> tapesIO);
  void SetMovement(string mov);

  string GetNext () { return next; }
  vector<tapeIO_t> GetTapesIO () { return tapesIO; }
  string GetMovement () { return movement; }
}
