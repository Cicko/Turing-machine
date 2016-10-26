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
	vector<State*> states;
	vector<string> inputSymbols;
	vector<string> tapeSymbols;
	string initialState;
	string whiteSymbol;
	vector<string> finals;   // Final states
	vector<Tape*> tapes;
	string actualState;
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
	void ReadInputSymbols (string symbols);
	void ReadTapeSymbols (string symbols);
	void ReadInitialState (string state);
	void ReadWhiteSymbol (string symbol);
	void ReadFinalStates (string states);
	void ReadNumTapes (string num);
	void ReadTransition (string trans);
};
