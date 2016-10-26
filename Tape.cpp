#include "Tape.hpp"


// Private methods
void Tape::MoveHeadToInit(){
	while(headPos != 0)
		MoveLeft();
}


void Tape::LoadInputToTape(vector<string> input){
	head = new Node (whiteSymbol);
  init = head;
	Node* node = new Node(whiteSymbol);
	head->SetLeft(node);

	while(inputLength < input.size()){       // Travel the whole input to know its size and
		cout << "Metemos" << input[inputLength] << endl;
		head->SetSymbol(input[inputLength++]);
    MoveRight();
	}
	MoveLeft();
	while(head->GetSymbol() != whiteSymbol){
		MoveLeft();
	}
	MoveRight();
	headPos = 0;
}


Tape::Tape(string white) {
	whiteSymbol = white;
  head = new Node(whiteSymbol);
	init = head;
	inputLength = 0;
	headPos = 0;
}

// Constructors
Tape::Tape(string white, vector<string> input) {
	whiteSymbol = white;
  head = NULL;
  init = NULL;
	headPos = 0;
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

bool Tape::IsEmpty() {
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


void Tape::ShowTape() {
	Node* aux = init->GetLeft();
	int it = -1;
	while(it <= inputLength) {
		cout << "| ";
		if(it == headPos)
			cout << "[" << aux->GetSymbol() << "] ";
		else
			cout << aux->GetSymbol() << " ";
		aux = aux->GetRight();
		it++;
	}
	cout << "|" << endl << endl;
}
