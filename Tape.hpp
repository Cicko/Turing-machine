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
#include <vector>
#include <string>

using namespace std;

class Tape{
	Node* head; // Para multipista creo que seria un vector de cabezas Node** cabezas
	Node* init;  // Node where the input starts. Its used just for showing the whole content.
	int headPos;
	int inputLength;
	string whiteSymbol;
public:
	Tape(string whiteSymbol);
	Tape(string whiteSymbol, vector<string> input);
	~Tape();
	void MoveRight();
	void MoveLeft();
	const bool IsEmpty();
	string Read();
	void Write(string c);
	const void ShowTape();
	void Movement(char mov);
private:
	void LoadInputToTape(vector<string> input);
	void MoveHeadToInit();
};
