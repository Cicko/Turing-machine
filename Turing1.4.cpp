/******


SIMULADOR DE M�QUINAS DE TURING

Creador : Rudolf Cicko
Versi�n : 1.4  // La definitiva
Fecha : 17-Nov-2014


*******/
//#include<stdio.h>
#include<iostream>
#include<fstream>
#include<cstdlib>

#define BLANCO '$'
#define ESTADO_INICIAL 0

using namespace std;





class nodo{
	char simbolo_;
	nodo* derecha_;
	nodo* izquierda_;
public:
	nodo();
	nodo(char simb);
	~nodo();
	void set_simbolo(char simb);
	char get_simbolo() ;
	void set_derecha(nodo* der);
	nodo* get_derecha();
	void set_izquierda(nodo* izq);
	nodo* get_izquierda();
};

//// CONSTRUCTOR Y DESTRUCTOR
nodo::nodo():simbolo_(BLANCO), derecha_(NULL), izquierda_(NULL){	}
nodo::nodo(char simb):simbolo_(simb), derecha_(NULL), izquierda_(NULL){ }
nodo::~nodo(){
	simbolo_= '$';
}



////// FUNCIONES P�BLICAS
void nodo::set_simbolo(char simb){
	simbolo_ = simb;
}
char nodo::get_simbolo() {
	return simbolo_;
}
void nodo::set_derecha(nodo* der){
	derecha_ = der;
}
nodo* nodo::get_derecha(){
	if(derecha_ == NULL){
		derecha_ = new nodo ();
	}
	return derecha_;
}
void nodo::set_izquierda(nodo* izq){
	izquierda_ = izq;
}
nodo* nodo::get_izquierda(){
	if(izquierda_ == NULL)
		izquierda_ = new nodo ();
	return izquierda_;
	}

class Cinta{
	nodo* cabeza; // Para multipista creo que seria un vector de cabezas nodo** cabezas
	nodo* inicio;
	int pos_cabeza;
	int longitud_cadena;
public:
	Cinta(char* entrada);
	~Cinta();
	void moverDerecha();
	void moverIzquierda();
	bool vacio();
	char leer();
	void escribir(char c);
	void mostrarCinta();
	void movimiento(char mov);
private:
	void colocarCadenaEnCinta(char* entrada);
	void colocarCabezaIzquierda();
};

void Cinta::colocarCabezaIzquierda(){
	while(pos_cabeza != 0)
		moverIzquierda();
}


void Cinta::colocarCadenaEnCinta(char* entrada){
	cabeza = new nodo ();
	inicio = cabeza;
	nodo* izquierda = new nodo();
	cabeza->set_izquierda(izquierda);
	//longitud_cadena++;

	while(entrada[longitud_cadena] != '\0'){ // Recorremos la cadena para saber su longitud
		cabeza->set_simbolo(entrada[longitud_cadena++]);
		moverDerecha();
	}
	moverIzquierda();
	while(cabeza->get_simbolo() != BLANCO){
		moverIzquierda();
	}
	moverDerecha();
	pos_cabeza = 0;
	cout << "Al introducir la cadena la cinta resultante : " << endl;
	mostrarCinta();
}
Cinta::Cinta(char* entrada):cabeza(NULL),longitud_cadena(0),inicio(NULL){
	colocarCadenaEnCinta(entrada);
}
Cinta::~Cinta(){
	cabeza = NULL; longitud_cadena = 0;
}
void Cinta::moverDerecha(){
	pos_cabeza++;
	nodo* aux = cabeza;
	cabeza = cabeza->get_derecha();
	cabeza->set_izquierda(aux);
}
void Cinta::moverIzquierda(){
	pos_cabeza--;
	nodo* aux = cabeza;
	cabeza = cabeza->get_izquierda();
	cabeza->set_derecha(aux);
}
void Cinta::movimiento(char mov){
	if(mov == 'L')
		moverIzquierda();
	else if(mov == 'R')
		moverDerecha();
	else if(mov == 'S');
	else
		cerr << "Error_02 : Eleccion incorrecta de movimiento" << endl;
}
bool Cinta::vacio(){ return (0==longitud_cadena); }

char Cinta::leer(){
	return cabeza->get_simbolo();
}
void Cinta::escribir(char c){
	if(cabeza->get_simbolo() == BLANCO)
		if(c != BLANCO)
			longitud_cadena++;
	cabeza->set_simbolo(c);
}
void Cinta::mostrarCinta(){
	//int recorredor = pos_cabeza;
	nodo* aux = inicio;
	aux = aux->get_izquierda();
	int recorredor = -1;
	while(recorredor <= longitud_cadena+1){
		cout << "| ";
		if(recorredor == pos_cabeza)
			cout << "[" << aux->get_simbolo() << "] " ;
		else
			cout << aux->get_simbolo() << " ";
		aux = aux->get_derecha();
		recorredor++;
	}
	cout << endl << endl;
}

typedef struct{
	char lectura;
	char escribe;
	char movimiento;
	int siguiente_estado;
}Transicion;

class Estado{
	Transicion* transiciones;
	int num_transiciones;
	bool final;
public:
	Estado();
	~Estado();
	void setFinal(bool f);
	bool esFinal();
	int getNumTransiciones();
	void maxTransicionesPosibles(int max);
	void nuevaTransicion(char lect, char escri, char mov, int siguiente);
	Transicion get_transicion(int inx);
};

//// CONSTRUCTOR Y DESTRUCTOR
Estado::Estado():
	transiciones(NULL),
	num_transiciones(0),
	final(false){ }
Estado::~Estado(){
	transiciones = NULL;
	final = false;
	num_transiciones = 0;
}

////// FUNCIONES P�BLICAS
void Estado::setFinal(bool f){
	final = f;
}
bool Estado::esFinal(){
	return final;
}
int Estado::getNumTransiciones(){
	return num_transiciones;
}
void Estado::maxTransicionesPosibles(int max){  // Definimos un tope de transiciones que equivale al n�mero de estados.
	if(transiciones == NULL)
		transiciones = new Transicion [ max ];
}
void Estado::nuevaTransicion(char lect, char escri, char mov, int siguiente){
	num_transiciones++;
	transiciones[num_transiciones-1].lectura = lect;
	transiciones[num_transiciones-1].escribe = escri;
	transiciones[num_transiciones-1].movimiento = mov;
	transiciones[num_transiciones-1].siguiente_estado = siguiente;
}
Transicion Estado::get_transicion(int inx){
		return transiciones[inx];
}

class Turing{
	int numEstados; // Numero de estados
	int numTransicionesTotal; // Numero de transiciones
	int final; // estado final, los superiores tambien lo son.
	//int ns_; // Numero de s�mbolos de entrada.
	Estado* Q_;
	Cinta* cinta_; // Para multicinta ser�a : �� Cinta** cintas_ ??
public:
	Turing();
	~Turing();
	void CargarMaquina();
	void mostrarMaquina();
	void SimulacionPasoPaso(bool paso_paso);
	void mostrarCinta();
	void comprobarFinales();
private:
	void definirFinales();
	void analizarCabecera();
	void analizarTuplas(int i, int estado, char movimiento, int siguiente);
};

///// CONSTRUCTOR Y DESTRUCTOR
Turing::Turing():
	numEstados(0),
	final(0),
	Q_(NULL),
	cinta_(NULL){ }

Turing::~Turing(){
	numEstados = 0;
	final = 0;
	Q_ = NULL;
	cinta_ = NULL;
}

///// FUNCIONES PRIVADAS
void Turing::definirFinales(){
	for(int i = 0;i < numEstados; i++)
			(i >= (final))? Q_[i].setFinal(true): Q_[i].setFinal(false);
}
void Turing::analizarCabecera(){
	if(numEstados < 1){                                                         //Revisar el n�mero de estados
		cerr << "Error : El numero de estados indicado en el fichero es incorrecto" << endl;
		system("exit");
	}
	if( final < 0 || final > numEstados ){                                  //Revisar los estados finales
		cerr << "Error : El estado final indicado en el fichero es incorrecto" << endl;
		cerr << "Vale " << final << " y deberia valer como mucho " << numEstados << endl;
		system("exit");
	}
}
void Turing::analizarTuplas(int i, int estado, char movimiento, int siguiente){
	if(estado < 0 || estado > numEstados){
		cerr << "Error en la linea " << i+4 << " del fichero " << endl;
		cerr << "Leyo estado " << estado << " y tiene que ser un valor entre 0 y " << numEstados-1 << endl;
		system("exit");
	}
	if(movimiento != 'L' && movimiento != 'R' && movimiento != 'S'){
		cerr << "Error a la hora de leer el movimiento en la linea " << i+4 << endl;
		cerr << "Leyo movimiento " << movimiento << " y solo puede ser 'L' , 'R' o 'S' ." << endl;
		system("exit");
	}
	if(siguiente < 0 || siguiente > numEstados){
		cerr << "Error en la linea " << i+4 << " del fichero " << endl;
		cerr << "Leyo siguiente " << estado << " y tiene que ser un valor entre 0 y " << numEstados-1 << endl;
		system("exit");
	}
}

//// FUNCIONES P�BLICAS
void Turing::CargarMaquina(){
	ifstream fich;
	char nombre[30];
	bool empieza = true;
	int estado,siguiente;
	char leer,escribir,movimiento;
	cout << "Introduzca el nombre del fichero : " ;
	cin >> nombre;
	fich.open(nombre);
	if(!fich.is_open()){
		cout << "Error_0: Problema a la hora de abrir el fichero" << endl;
		system("exit");
	}
	fich >> numEstados;
	fich >> final;
	fich >> numTransicionesTotal;
	analizarCabecera();
	Q_ = new Estado [numEstados];
	definirFinales();
		for(int i = 0; i < numTransicionesTotal; i++){
			fich >> estado;
			fich >> leer;
			fich >> escribir;
			fich >> movimiento;
			fich >> siguiente;
			analizarTuplas(i,estado,movimiento,siguiente);
			Q_[estado].maxTransicionesPosibles(numTransicionesTotal);
			Q_[estado].nuevaTransicion(leer,escribir,movimiento,siguiente);
		}
	fich.close();
}
void Turing::mostrarMaquina(){
	if(Q_ == NULL)
		cout << endl << "Primero debe cargar la maquina desde un fichero " << endl;
	else
	{
		Transicion transicion;
		cout << endl << "MAQUINA DE TURING CARGADA : " << endl << endl << endl;
		cout << numEstados << endl;
		cout << final << endl;
		cout << numTransicionesTotal << endl;
		for(int i = 0;i < numEstados; i++){
			for(int j = 0;j < Q_[i].getNumTransiciones() ;j++){
				transicion = Q_[i].get_transicion(j); // la variable transicion contiene la transicion j del estado i.
				cout << i << " ";
				cout << transicion.lectura << " ";
				cout << transicion.escribe << " ";
				cout << transicion.movimiento << " ";
				cout << transicion.siguiente_estado << " ";
				cout << endl;
			}
		}
	}
}
void Turing::SimulacionPasoPaso(bool paso_paso){
	if(Q_ == NULL)
		cout << endl << "Primero debe cargar la maquina desde un fichero " << endl;
	else
	{
		char opc;
		char cadena[100];
		int estado_actual = ESTADO_INICIAL;
		cout << "Introduzca una cadena a analizar: " ;
		cin >> cadena;
		cinta_ = new Cinta(cadena);
		cout << "Cinta inicial : " << endl;
		cout << endl ;
		cin.get();
		for(int i = 0; i < Q_[estado_actual].getNumTransiciones() ; i++){
			Transicion Tactual = Q_[estado_actual].get_transicion(i);
			if(Tactual.lectura == cinta_->leer()){
					if(paso_paso){
						cinta_->mostrarCinta();
						cout << "Estado actual : " << estado_actual << endl ;
						cout << "Lee : '" << cinta_->leer() << "' -----> escribe '" << Tactual.escribe << "' " << endl ;
						cout << "Moviendose a " << Tactual.movimiento << endl ;
						cout << endl << endl;
					}
				cinta_->escribir(Tactual.escribe);
				cinta_->movimiento(Tactual.movimiento);
				estado_actual = Tactual.siguiente_estado;
				i = -1; // Le obligamos a repetir el for con i=0
					if(paso_paso){
						cout <<"Introduzca Enter para siguiente paso:";
						cin.get();
						system("clear");
					}
			}
		}
		cout << "Cinta final : " << endl;
		cinta_->mostrarCinta();
		cout << "Termina en estado : " << estado_actual << endl;
		if(Q_[estado_actual].esFinal())
			cout << endl << "La cadena es aceptada" << endl;
		else
			cout << endl << "La cadena no es aceptada" << endl;
	}
}
int main(int argc, char *argv[]) {
	Turing turing;
	int opcion = 0;

	cout << endl << endl <<"Bienvenido al Simulador de Maquinas de Turing" << endl;

	while(opcion != 4){
		cout << endl << endl << "MENU : " << endl;
		cout << "    1.Leer Maquina." << endl;
		cout << "    2.Mostrar Maquina." << endl;
		cout << "    3.Simular Maquina. " << endl;
		cout << "    4.Salir." << endl;
		cout << endl << endl << "Introduzca opcion : " ;
		cin >> opcion;
		system("clear");
		switch(opcion){
			case 1:
				turing.CargarMaquina();
				break;
			case 2:
				turing.mostrarMaquina();
				break;
			case 3:
				char opc;
				cout << endl << "� Desea visualizar paso a paso el procedimiento ? (S/N) : " ;
				cin >> opc;
				switch(opc){
					case 'S' : turing.SimulacionPasoPaso(true);
							   break;
					case 'N' : turing.SimulacionPasoPaso(false);
							   break;
					default : cout << "Eleccion incorrecta, volviendo al menu principal.." << endl;
								break;
				}
				break;
			case 4:
				return 0;
			default:
				cout << "Ha introducido una opcion incorrecta" << endl << endl;
		}
	}
}
