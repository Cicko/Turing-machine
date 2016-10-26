#include "Turing.hpp"
#include <iostream>

using namespace std;

int main(int argc, char * argv[]) {
	Turing * turing;
	int option = 0;
	bool loaded = false;


	cout << endl << endl <<"Welcome to Turing Machine Simulator." << endl;

	while(option != 4){
		cout << endl << endl << "MENU : " << endl;
		cout << "    1.Load Turing machine." << endl;
		cout << "    2.Show Turing machine." << endl;
		cout << "    3.Simulate. " << endl;
		cout << "    4.Exit." << endl;
		cout << endl << endl << "Insert option: " ;
		cin >> option;
		cout << endl;
		switch(option) {
			case 1:
        turing = new Turing();
				loaded = turing->LoadedMachine();
				break;
			case 2:
				if (loaded)
        	turing->ShowMachine();
				else
					cout << "You have to load the Machine first." << endl;
				break;
			case 3:
				char opc;
				bool verbose;
				if (loaded) {
					cout << endl << "Do you want to see it step by step execution? (S/N) : " ;
					cin >> opc;
					switch(opc) {
						case 'S':
             	verbose = true;
             	turing->Simulate(verbose);
					   	break;
						case 'N' :
             	verbose = false;
             	turing->Simulate(verbose);
						 	break;
						default : cout << "Incorrect election, returning to the main menu.." << endl;
							break;
					}
				}
				else {
					cout << "You have to load the Machine first." << endl;
				}
				break;
			case 4:
        cout << "Exiting.." << endl;
				break;
			default:
				cout << "You have inserted an incorrect option." << endl << endl;
		}
	}
  return 0;
}
