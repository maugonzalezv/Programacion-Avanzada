#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    try {
        srand(time(0));
        
        string opciones[3] = {"piedra", "papel", "tijera"};
        string jugador;
        int computadora;
        int ronda = 0;
        
        while(true) {
            ronda++;
            cout << "piedra, papel o tijera!" << endl;
            
            if(!(cin >> jugador)) {
                cerr << "error leyendo entrada" << endl;
                break;
            }
            
            computadora = rand() % 3;
            cout << opciones[computadora] << endl;
            
            int j = -1;
            if(jugador == "piedra") j = 0;
            if(jugador == "papel") j = 1;
            if(jugador == "tijera") j = 2;
            
            if(j == -1) {
                cout << "opcion invalida!" << endl;
                continue;
            }
            
            if(j == computadora) {
                cout << "empate!" << endl;
            }
            else if((j == 0 && computadora == 2) || 
                    (j == 1 && computadora == 0) || 
                    (j == 2 && computadora == 1)) {
                cout << "ganaste!" << endl;
            }
            else {
                cout << "perdiste!" << endl;
            }
            
            cout << endl;
        }
    }
    catch(...) {
        cerr << "error fatal en el juego" << endl;
        return 1;
    }
    
    return 0;
}