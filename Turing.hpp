#include <iostream>
#include <set>
#include <string>
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
	State* initialState;
	string whiteSymbol;
	vector<string> finals;   // Final states
	vector<Tape*> tapes;
	State* actualState;
	bool loadedMachine;
public:
	Turing();
	~Turing();
	int LoadMachine ();
	int LoadedMachine () { return loadedMachine; }

	void ShowMachine ();
	void ShowStates ();
	void ShowInputSymbols ();
	void ShowTapeSymbols ();
	void ShowInitialState ();
	void ShowWhiteSymbol ();
	void ShowFinalStates ();
	void ShowNumTapes ();
	void ShowTransitions ();

	void ShowErrors (int error);

	unsigned GetNumTapes () { return tapes.size(); }
	unsigned GetNumStates () { return states.size(); }
	unsigned GetNumInputSymbols () { return inputSymbols.size(); }
	unsigned GetNumTapeSymbols () { return tapeSymbols.size(); }

	void Simulate(bool verbose);  // If verbose then is step by step simulation.
	void ShowAllTapesContent();

private:
	void AnalyzeTuple(int i, int state, char movement, int next);
	int LoadStates (string states);
	int LoadInputSymbols (string symbols);
	int LoadTapeSymbols (string symbols);
	int LoadInitialState (string state);
	int LoadWhiteSymbol (string symbol);
	int LoadFinalStates (string states);
	int LoadNumTapes (string num);
	int LoadTransition (string trans);
	

	bool StateExists (string id);

	void FillTapes ();
	State* GetStateById (string id);
	bool CorrectTransition (Transition* tran);
};
