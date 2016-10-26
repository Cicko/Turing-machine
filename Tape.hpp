/**
*
* @author: Rudolf Cicko
* @subject: Complejidad computacional (computational complexity), Universidad de La Laguna
* @date: 22-October-2016
* @description: This class represent a Input Tape in the Turing Machine. The input is loaded into the tape.
*
**/
#include "Node.hpp"
#include <iostream>

using namespace std;

class Tape{
	Node* head; // Para multipista creo que seria un vector de cabezas Node** cabezas
	Node* init;  // Node where the input starts. Its used just for showing the whole content.
	int headPos;
	int inputLength;
public:
	Tape();
	Tape(char* input);
	~Tape();
	void MoveRight();
	void MoveLeft();
	const bool IsEmpty();
	const char Read();
	void Write(char c);
	const void ShowTape();
	void Movement(char mov);
private:
	void LoadInputToTape(char* entrada);
	void MoveHeadToInit();
};
