#include <iostream>
#include <set>
#include <fstream>
#include <vector>
#include "State.hpp"
#include "Utils.hpp"
#include "Tape.hpp"

#define INITIAL_STATE 0

using namespace std;

class Turing {
	State* initialState;
	vector<State*> states;
	vector<State*> finals;
	vector<Tape*> tapes; // Para multicinta ser�a : �� Cinta** cintas_ ??
	vector<string> tapeSymbols;
public:
	Turing();
	~Turing();
	void LoadMachine();
	void ShowMachine();
	void Simulate(bool verbose);  // If verbose then is step by step simulation.
//	void comprobarFinales();
private:
	void SetFinals();
	void CheckFileHead();
	void SetNumTapes(unsigned);
	void AnalyzeTuple(int i, int state, char movement, int next);
	void ReadStates (string states);
	void ReadTapeSymbols (string symbols);
};
