#include "Transition.hpp"

typedef struct{
	char reads;
	char writes;
	char movement;
	int nextState;
} Transition;

class State{
	Transition* transitions;
	int numTransitions;
	bool final;
public:
	State();
	~State();
	void SetFinal(bool f);
	const bool IsFinal();
	const int GetNumTransitions();
	void SetMaxPossibleTrans(int max);  // Set maximum possible transitions
	void NewTransition(char lect, char escri, char mov, int siguiente);
	Transition get_transicion(int inx);
};

//// CONSTRUCTOR Y DESTRUCTOR
State::State() {
  transitions = NULL;
  numTransitions = 0;
  final = false;
}

State::~State() {
	transitions = NULL;
	final = false;
	numTransitions = 0;
}

////// FUNCIONES PúBLICAS
void State::SetFinal(bool f){
	final = f;
}

bool State::IsFinal(){
	return final;
}

const int State::GetNumTransitions(){
	return num_transiciones;
}

void State::SetMaxPossibleTrans(int max){  // Definimos un tope de transiciones que equivale al n�mero de States.
	if(transiciones == NULL)
		transiciones = new Transicion [max];
}

void State::nuevaTransicion(char lect, char escri, char mov, int siguiente){
	transiciones[num_transiciones].lectura = lect;
	transiciones[num_transiciones].escribe = escri;
	transiciones[num_transiciones].movimiento = mov;
	transiciones[num_transiciones].siguiente_State = siguiente;
  num_transiciones++;
}

Transition State::GetTransition(int inx){
		return transitions[inx];
}
