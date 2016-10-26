#include "Tape.hpp"


// Private methods
void Tape::MoveHeadToInit(){
	while(headPos != 0)
		MoveLeft();
}

/*
void Tape::LoadInputFromKeyboard () {
	cout << "Insert input: "
}
*/

void Tape::LoadInputToTape (vector<string> input) {
	head = new Node(whiteSymbol);
	init = head;
	Node* node = new Node(whiteSymbol);
	head->SetLeft(node);

	for (int i = 0; i < input.size(); i++) {
		head->SetSymbol(input[0]);
		MoveRight();
	}
}

/*
void Tape::LoadInputToTape(vector<string> input){
	head = new Node ();
  init = head;
	Node* node = new Node();
	head->SetLeft(node);
	//inputLength++;

	while(input[inputLength] != '\0'){       // Travel the whole input to know its size and
		head->SetSymbol(input[inputLength++]);
    MoveLeft();
	}
	MoveLeft();
	while(head->GetSymbol() != WHITE){
		MoveLeft();
	}
	MoveRight();
	headPos = 0;
	cout << "Tape content: " << endl;
	ShowTape();
}
*/

Tape::Tape(string white) {
	whiteSymbol = white;
  head = NULL;
	init = NULL;
	inputLength = 0;
}

// Constructors
Tape::Tape(string white, vector<string> input) {
	whiteSymbol = white;
  head = NULL;
  init = NULL;
  inputLength = input.size();;
  LoadInputToTape(input);
}

Tape::~Tape(){
	head = NULL;
	inputLength = 0;
}

// public methods
void Tape::MoveRight(){
	headPos++;
	Node* aux = head;
	head = head->GetRight();
	head->SetLeft(aux);
}

void Tape::MoveLeft(){
	headPos--;
	Node* aux = head;
	head = head->GetLeft();
	head->SetRight(aux);
}

void Tape::Movement(char mov){
	if(mov == 'L')
		MoveLeft();
	else if(mov == 'R')
		MoveRight();
	else if(mov == 'S');  // Do nothing
	else
		cerr << "Error_02: Incorrect movement. The movement " << mov << " is not recognized." << endl;
}

const bool Tape::IsEmpty() {
  return (0 == inputLength);
}

string Tape::Read() {
	return head->GetSymbol();
}


// ARREGLAR
void Tape::Write(string c){
	if(head->GetSymbol() == whiteSymbol)
    if(c != whiteSymbol)
			inputLength++;
	head->SetSymbol(c);
}


const void Tape::ShowTape() {
	Node* aux = init;
	aux = aux->GetLeft();
	int it = -1;
	while(it <= inputLength + 1){
		cout << "| ";
		if(it == headPos)
			cout << "[" << aux->GetSymbol() << "] " ;
		else
			cout << aux->GetSymbol() << " ";
		aux = aux->GetRight();
		it++;
	}
	cout << "|" << endl << endl;
}
