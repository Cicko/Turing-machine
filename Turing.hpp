#include <iostream>
#include <set>
#include <fstream>
#include <vector>
#include "State.hpp"
#include "Tape.hpp"

#define INITIAL_STATE 0

using namespace std;

class Turing {
	int numStates;  // Numero de states
	int numTrans;   // Numero de transitiones
	int final;      // all states with index higher than final are final states.
	//int ns_; // Numero de s�mbolos de entrada.
	State* states;
	//set<State> states;
	//vector<Tape> tapes; // Para multicinta ser�a : �� Cinta** cintas_ ??
	Tape* tapes;
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
	void AnalyzeTuple(int i, int state, char movement, int next);
};
