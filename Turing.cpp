#include "Turing.hpp"

#define LOADING_ERROR -1
#define EXCEPTION_ERROR -1
#define NO_FILE_ERROR -1

#define SUCCESS 0
#define NO_STATES_ERROR -1
#define NO_INITIAL_STATE_FOUND -2
#define NO_WHITE_SYMBOL_ERROR -3
#define NO_FINAL_FOUND -4
#define NUM_TAPES_ERROR -5
#define TRANS_STATE_ERROR -6






///// CONSTRUCTOR Y DESTRUCTOR
Turing::Turing(){
	loadedMachine = false;
	if (LoadMachine() == 0) {
		loadedMachine = true;
		cout << "Turing Machine successfully loaded!." << endl;
	}
}

Turing::~Turing(){
}


int Turing::LoadMachine() {
	ifstream file;
	string fileName;
	cout << "Insert the file name: ";
	cin >> fileName;

	try {
  	file.open(fileName.c_str(), ios::in);
		if(file.fail()) cerr << "Error: " << strerror(errno) << endl;

	  if (file.is_open()) {
	      string temp;
				int success = SUCCESS;
				bool wasError = false;
				auto check = [&](void) {
					if (success != SUCCESS) {
						cerr << "ERROR: ";
						ShowErrors(success);
						wasError = true;
					}
				};
	      getline (file, temp);
	      success = LoadStates (temp);
				check();
	      getline (file, temp);
		    success = LoadInputSymbols (temp);
				check();
				getline (file, temp);
	    	success = LoadTapeSymbols(temp);
				check();
	      getline (file, temp);
	      success = LoadInitialState(temp);
				check();
	      getline (file, temp);
	      success = LoadWhiteSymbol(temp);
				check();
	      getline (file, temp);
	      success = LoadFinalStates (temp);
				check();
				getline (file, temp);
				success = LoadNumTapes (temp);
				check();

				if (wasError) return LOADING_ERROR;

	    	while (true) {
	      	getline (file, temp);
					if (temp.size() < 1) break; // We reach the end of file.
	      	LoadTransition (temp);
	    	}
	      file.close();
				return 0;
	  }
	  else {
	    cout << "El fichero no existe" << endl;
			return NO_FILE_ERROR;
	  }
	}
	catch (exception e) {
		std::cerr << e.what() << endl;
		return EXCEPTION_ERROR;
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
	cout << "Initial state: " << initialState->GetId() << endl;
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
	cout << "Transitions (format: ((read), (write, movement)): " << endl;
	for (int i = 0; i < GetNumStates(); i++) {
		states[i]->ShowAllTransitions();
	}
}


void Turing::ShowErrors (int error) {
	switch (error) {
		case SUCCESS:
			break;
		case NO_STATES_ERROR:
			cerr << "There are no states in the machine definition.." << endl;
			break;
		case NO_INITIAL_STATE_FOUND:
			cerr << "The initial state can not be found.." << endl;
			break;
		case NO_WHITE_SYMBOL_ERROR:
			cerr << "The machine have no specified the white symbol.." << endl;
			break;
		case NO_FINAL_FOUND:
			cerr << "The final states are incorrect.." << endl;
			break;
		case NUM_TAPES_ERROR:
			cerr << "The number of tapes have to be at least 1" << endl;
			break;
		case TRANS_STATE_ERROR:
			cerr << "The state of the transition does not exist" << endl;
			break;
		default:
			cerr << "Unknown error" << endl;
	}
}


///// FUNCIONES PRIVADAS
int Turing::LoadStates (string statesStr) {
	vector<string> aStates = utils::lineToStrings (statesStr, " ");
	if (aStates.size() < 1) return NO_STATES_ERROR;
	for (int i = 0; i < aStates.size(); i++) {
			State* newState = new State(aStates[i]);
			states.push_back(newState);
	}
	return SUCCESS;
}

int Turing::LoadInputSymbols (string symbols) {
	inputSymbols = utils::lineToStrings (symbols, " ");
	return SUCCESS;
}

int Turing::LoadTapeSymbols (string symbols) {
  tapeSymbols = utils::lineToStrings (symbols, " ");
	return SUCCESS;
}

int Turing::LoadInitialState (string state) {
	for (int i = 0; i < GetNumStates(); i++) {
		if(states[i]->GetId() == state) {
			initialState = states[i];
			actualState = initialState;
			return SUCCESS;
		}
	}
	return NO_INITIAL_STATE_FOUND;
}

int Turing::LoadWhiteSymbol (string symbol) {
	whiteSymbol = symbol;
	if (whiteSymbol == "") return NO_WHITE_SYMBOL_ERROR;
	return SUCCESS;
}

int Turing::LoadFinalStates (string statesStr) {
	finals = utils::lineToStrings(statesStr, " ");
	bool finalFound = false;

	for (int i = 0; i < finals.size(); i++) {
		for (int j = 0; j < states.size(); j++) {
			if (finals[i] == states[j]->GetId()) {
				states[j]->SetFinal(true);
				finalFound = true;
			}
		}
	}
	if (finalFound) return SUCCESS;
	else return NO_FINAL_FOUND;
}

int Turing::LoadNumTapes (string num) {
	int numTapes = stoi(num);
	if (numTapes < 1) return NUM_TAPES_ERROR;
	for (int i = 0; i < numTapes; i++) {
		tapes.push_back(new Tape(whiteSymbol));
	}
	return SUCCESS;
}

int Turing::LoadTransition (string trans) {
	vector<string> transition = utils::lineToStrings(trans, " ");
	string transOrigState = transition[0];  // Transition's origin state
	if (!StateExists(transOrigState)) {
		cerr << "The state " << transOrigState << " does not exist.." << endl;
		return TRANS_STATE_ERROR;
	}
	else {
		for (int i = 0; i < states.size(); i++) {
			if (transOrigState == states[i]->GetId()) {
				states[i]->NewTransition(trans, tapes.size());
				return SUCCESS;
			}
		}
	}
}

bool Turing::StateExists (string id) {
	for (int i = 0; i < GetNumStates(); i++) {
		if (id == states[i]->GetId()) return true;
	}
	return false;
}

void Turing::Simulate (bool verbose) {
	if (!LoadedMachine())
		cout << "You have to load the machine first" << endl;
	else {
		actualState = initialState;
		FillTapes ();
		cout << "Initial Tapes content: " << endl;
		ShowAllTapesContent();

		for (int i = 0; i < actualState->GetNumTransitions(); i++) {
			Transition * actualTrans = actualState->GetTransition(i);
			if (CorrectTransition(actualTrans)) {
				if (verbose)
					actualTrans->ShowTransition();

				actualState = GetStateById(actualTrans->GetTo());

				for (int j = 0; j < GetNumTapes(); j++) {
					tapes[j]->Write(actualTrans->GetTapesWM()[j].first);  // first --> Writes
					tapes[j]->Movement(actualTrans->GetTapesWM()[j].second); // second --> Movement
				}
				if (verbose) {
					ShowAllTapesContent();
					cout << endl;
				}
				i = -1;
			}
		}
		if (actualState->IsFinal()) {
			cout << "Result: " << endl;
			ShowAllTapesContent();
			cout << "The input is accepted!! Congratulations" << endl;
		}
		else
			cout << "Sorry... but you input is not accepted.." << endl;
	}
}


void Turing::FillTapes () {
	for (int i = 0;i < GetNumTapes(); i++) {
		cout << "Insert input for the tape " << i << " (type 'quit' to finish it): " << endl;
		int length = 0;
		string symbol;
		vector<string> inputTape;
		do {
			cout << "Insert symbol " << length++ << ": ";
			cin >> symbol;
			if (symbol != "quit")
				inputTape.push_back(symbol);
		} while (symbol != "quit");
		tapes[i]->LoadInputToTape(inputTape);
	}
}

void Turing::ShowAllTapesContent () {
	for (int i = 0; i < GetNumTapes(); i++) {
		cout << "Tape " << i << ": ";
		tapes[i]->ShowTape();
	}
}

State* Turing::GetStateById (string id) {
	for (int i = 0; i < GetNumStates(); i++) {
		if (id == states[i]->GetId())
			return states[i];
	}
}

// It compare the symbols at the tapes and the input symbols of the transition.
bool Turing::CorrectTransition (Transition* trans) {
	for (int i = 0; i < GetNumTapes(); i++) {
		if (tapes[i]->Read() != trans->GetInput()[i]) {
			return false;
		}
	}
	return true;
}
