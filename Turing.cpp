#include "Turing.hpp"

///// CONSTRUCTOR Y DESTRUCTOR
Turing::Turing(){
	numStates = 0;

	final = 0;
	states = NULL;
	tapes = NULL;
}

Turing::~Turing(){
	numStates = 0;
	final = 0;
	states = NULL;
	tapes = NULL;
}

///// FUNCIONES PRIVADAS
void Turing::ReadStates (string states) {
	vector<string> aStates = utils::lineToStrings (states, " ");
	for (int i = 0;i < aStates.size(); i++) {
			states.push_back(new State(aStates[i]));
	}
}

void PushDownAutomaton::ReadTapeSymbols (string symbols) {
  tapeSymbols = utils::lineToStrings (symbols, " ");
}

void Turing::SetFinals() {
	for(int i = 0;i < numStates; i++)
			(i >= (final))? states[i].SetFinal(true): states[i].SetFinal(false);
}

void Turing::SetNumTapes(unsigned num) {
	for (int i = 0;i < num; i++) {
		tapes.add(new Tape)
	}
}

void Turing::CheckFileHead() {
	if (numStates < 1) {
		cerr << "Error: The number of states is incorrect." << endl;
		system("exit");
	}
	if (final < 0 || final > numStates) {
		cerr << "Error : The final state starter is incorrect" << endl;
		system("exit");
	}
}

void Turing::AnalyzeTuple(int i, int state, char movement, int next) {
	if(state < 0 || state > numStates){
		cerr << "Error at line " << i+4 << " in the file. " << endl;
		cerr << "The state " << state << " should be between 0 and " << numStates-1 << endl;
		system("exit");
	}
	if(movement != 'L' && movement != 'R' && movement != 'S'){
		cerr << "Error when reads the movement at line " << i+4 << endl;
		cerr << "It was movement " << movement << " and only can be 'L' , 'R' or 'S' ." << endl;
		system("exit");
	}
	if(next < 0 || next > numStates){
		cerr << "Error at line " << i+4 << " in the file. " << endl;
		cerr << "State " << state << " have to be between 0 and " << numStates-1 << endl;
		system("exit");
	}
}

void Turing::LoadMachine() {
	ifstream file;
	char name[40];
	cout << "Insert the file name: ";
	cin >> name;
  file.open(name);
  if (file.is_open()) {
      string temp;
      getline (file, temp);
      ReadStates (temp);
      getline (file, temp);
      readInputSymbols(temp);
      getline (file, temp);
      readStackSymbols(temp);
      getline (file, temp);
      readInitialState(temp);
      getline (file, temp);
      readInitialStackSymbol (temp);
      getline (file, temp);
      readFinalStates (temp);
      while (!file.eof()) {
        getline (file, temp);
        saveTransition (temp);
      }
      file.close();
  }
  else {
    cerr << "El fichero no existe" << endl;
  }
}

/*
//// Public functions
void Turing::LoadMachine(){
	ifstream fich;
	char name[40];
	int state,next;
	char reads,writes,movement;
	cout << "Insert the file name: ";
	cin >> name;
	fich.open(name);
	if(!fich.is_open()){
		cout << "Error_0: Error occurs during file opening." << endl;
		system("exit");
	}
	fich >> numStates;

	fich >> final;
	fich >> numTrans;
	CheckFileHead();
	//states = new State [numStates];
	SetFinals();
	// Loading transitions
	for(int i = 0; i < numTrans; i++){
		State newState;
		fich >> state;
		fich >> reads;
		fich >> writes;
		fich >> movement;
		fich >> next;
		AnalyzeTuple(i,state,movement,next);
		newState.NewTransition(reads,writes,movement,next);
		states.push_back(newState);
		//states[state].NewTransition(reads,writes,movement,next);
	}
	fich.close();
}
*/

void Turing::ShowMachine(){
	if(states == NULL)
		cout << endl << "You have to load the machine first. " << endl;
	else {
		Transition transition;
		cout << endl << "TURING MACHINE: " << endl << endl << endl;
		cout << states.size() << endl;
		cout << final << endl;
		cout << numTrans << endl;
		for(int i = 0; i < states.size(); i++) {
			for(int j = 0; j < states[i].GetNumTransitions(); j++) {
				transition = states[i].GetTransition(j); // la variable transition contiene la transition j del state i.
				cout << i << " ";
				cout << transition.reads << " ";
				cout << transition.writes << " ";
				cout << transition.movement << " ";
				cout << transition.nextState << " ";
				cout << endl;
			}
		}
	}
}
void Turing::Simulate(bool verbose){
	if(states == NULL)
		cout << endl << "You have to load the Turing machine first.  " << endl;
	else {
		char opc;
		char cadena[100];
		int actualState = initialState;
		cout << "Insert an input string: ";
		cin >> cadena;
		tapes = new Tape(cadena);
		cout << "Initial Tape : " << endl;
		cout << endl ;
		cin.get();
		for(int i = 0; i < states[actualState].GetNumTransitions(); i++) {
			Transition Tactual = states[actualState].GetTransition(i);
			if(Tactual.reads == tapes->-Read()) {
				if(verbose) {
					tapes->ShowTape();
					cout << "State actual : " << actualState << endl ;
					cout << "Read : '" << tapes->Read() << "' -----> writes '" << Tactual.writes << "' " << endl ;
					cout << "Moving to " << Tactual.movement << endl ;
					cout << endl << endl;
				}
				tapes->Write(Tactual.writes);
				tapes->Movement(Tactual.movement);
				actualState = Tactual.nextState;
				i = -1; // Le obligamos a repetir el for con i=0
					if(verbose) {
						cout <<"Press Return button to next step:";
						cin.get();
						system("clear");
					}
			}
		}
		cout << "Final tape: " << endl;
		tapes->ShowTape();
		cout << "Finished at state: " << actualState << endl;
		if(states[actualState].IsFinal())
			cout << endl << "The input is accepted" << endl;
		else
			cout << endl << "The input is NOT accepted" << endl;
	}
}
