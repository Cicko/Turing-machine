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
void Turing::LoadStates (string states) {
	vector<string> aStates = utils::lineToStrings (states, " ");
	for (int i = 0;i < aStates.size(); i++) {
			states.push_back(new State(aStates[i]));
	}
}

void Turing::LoadInputSymbols (string symbols) {
	inputSymbols = utils::lineToStrings (symbols, " ");
}

void Turing::LoadTapeSymbols (string symbols) {
  tapeSymbols = utils::lineToStrings (symbols, " ");
}

void Turing::LoadInitialState (string state) {
  initialState = state;
  actualState = initialState;
}

void Turing::LoadWhiteSymbol (string symbol) {
	whiteSymbol = symbol;
}

void Turing::LoadFinalStates (string states) {
	finals = utils::lineToStrings(states, " ");
}

void Turing::LoadNumTapes (string num) {
	int numTapes = stoi(num);
	for (int i = 0;i < numTapes; i++) {
		tapes.push_back(new Tape());
	}
}

void Turing::LoadTransition (string trans) {
	vector<string> transition = utils::lineToStrings(trans, " ");
	string transOrigState = transition[0];  // Transition's origin state
	for (int i = 0; i < states.size(); i++) {
		if (transOrigState == states[i]->GetId()) {
			states[i]->NewTransition(trans, tapes.size());
			return;
		}
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
      LoadStates (temp);
      getline (file, temp);
	    LoadInputSymbols (temp);
			getline (file, temp);
      LoadTapeSymbols(temp);
      getline (file, temp);
      LoadInitialState(temp);
      getline (file, temp);
      LoadWhiteSymbol(temp);
      getline (file, temp);
      LoadFinalStates (temp);
			getline (file, temp);
			LoadNumTapes (temp);
      while (!file.eof()) {
        getline (file, temp);
        LoadTransition (temp);
      }
      file.close();
  }
  else {
    cerr << "El fichero no existe" << endl;
  }
}


void Turing::ShowMachine(){
	if(GetNumStates() == 0)
		cout << endl << "You have to load the machine first. " << endl;
	else {
		cout << endl << "---- TURING MACHINE ---- " << endl << endl << endl;
		ShowStates();
		ShowInputSymbols();
		ShowTapeSymbols ();
		ShowInitialState ();
		ShowWhiteSymbol ();
		ShowFinalStates ();
		ShowNumTapes ();
		ShowTransitions ();
	}
}

void Turing::ShowStates () {
	cout << "States: {";
	for (int i = 0; i < GetNumStates(); i++) {
		cout << states[i]->GetId();
		if (i < GetNumStates() - 1)
			cout << ", ";
		else
			cout << "}" << endl;
	}
}

void Turing::ShowInputSymbols () {
	cout << "Input symbols: {";
	for (int i = 0; i < GetNumInputSymbols(); i++) {
		cout << inputSymbols[i];
		if (i < GetNumInputSymbols() - 1)
			cout << ", ";
		else
			cout << "}" << endl;
	}
}
void Turing::ShowTapeSymbols () {
	cout << "Tape symbols: {";
	for (int i = 0; i < GetNumTapeSymbols(); i++) {
		cout << tapeSymbols[i];
		if (i < GetNumTapeSymbols() - 1)
			cout << ", ";
		else
			cout << "}" << endl;
	}
}
void Turing::ShowInitialState () {
	cout << "Initial state: " << initialState << endl;
}
void Turing::ShowWhiteSymbol () {
	cout << "White symbol: " << whiteSymbol << endl;
}
void Turing::ShowFinalStates () {
	cout << "Final states: {";
	for (int i = 0; i < GetNumStates(); i++) {
		if (states[i]->IsFinal()) {
			cout << states[i]->GetId();
			if (i < GetNumStates() - 1)
				cout << ", ";
			else
				cout << "}" << endl;
		}
	}
}

void Turing::ShowNumTapes () {
	cout << "Number of tapes: " << GetNumTapes() << endl;
}
void Turing::ShowTransitions () {
	cout << "Transitions: " << endl;
	for (int i = 0; i < GetNumStates(); i++) {
		states[i]->ShowAllTransitions();
	}
}
/*
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
*/
