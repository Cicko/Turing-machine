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
	void LoadMachine ();

	void ShowMachine ();
	void ShowStates ();
	void ShowInputSymbols ();
	void ShowTapeSymbols ();
	void ShowInitialState ();
	void ShowWhiteSymbol ();
	void ShowFinalStates ();
	void ShowNumTapes ();
	void ShowTransitions ();

	unsigned GetNumTapes () { return tapes.size(); }
	unsigned GetNumStates () { return states.size(); }
	unsigned GetNumInputSymbols () { return inputSymbols.size(); }
	unsigned GetNumTapeSymbols () { return tapeSymbols.size(); }

	void Simulate(bool verbose);  // If verbose then is step by step simulation.

private:
	void AnalyzeTuple(int i, int state, char movement, int next);
	void LoadStates (string states);
	void LoadInputSymbols (string symbols);
	void LoadTapeSymbols (string symbols);
	void LoadInitialState (string state);
	void LoadWhiteSymbol (string symbol);
	void LoadFinalStates (string states);
	void LoadNumTapes (string num);
	void LoadTransition (string trans);
};
