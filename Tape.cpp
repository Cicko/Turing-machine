#include "Tape.hpp"


// Private methods
void Tape::MoveHeadToInit(){
	while(headPos != 0)
		MoveLeft();
}

void Tape::LoadInputToTape(char* input){
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

Tape::Tape() {
  head = NULL;
	init = NULL;
	inputLength = 0;
}

// Constructors
Tape::Tape(char* input) {
  head = NULL;
  init = NULL;
  inputLength = 0;
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

const char Tape::Read() {
	return head->GetSymbol();
}

void Tape::Write(char c){
	if(head->GetSymbol() == WHITE)
    if(c != WHITE)
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
