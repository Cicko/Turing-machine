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


// Constructors
Tape::Tape(char* input) {
  cabeza = NULL;
  init = NULL;
  inputLength = 0;
  LoadInputToTape(input);
}

Tape::~Tape(){
	cabeza = NULL; inputLength = 0;
}

// public methods
void Tape::MoveRight(){
	headPos++;
	Node* aux = head;
	head = head->GetRight();
	head->SetLeft(aux);
}

void Tape::moverIzquierda(){
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

bool Tape::IsEmpty() const{
  return (0 == inputLength);
}

char Tape::Read() const{
	return head->GetSymbol();
}

void Tape::Write(char c){
	if(head->GetSymbol() == WHITE)
    if(c != WHITE)
			inputLength++;
	head->SetSymbol(c);
}


void Tape::ShowTape() const{
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
