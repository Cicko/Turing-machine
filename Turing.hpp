

class Turing{
	int numEstados;  // Numero de estados
	int numTransicionesTotal; // Numero de transiciones
	int final;       // estado final, los superiores tambien lo son.
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
