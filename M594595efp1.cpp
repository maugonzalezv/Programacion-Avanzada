#include <iostream>

using namespace std;

int main() {
    try {
        char tablero[6][7];
        int col;
        int turno = 0;
        char ficha;
        int fila;
        int gano;
        
        for(int i = 0; i < 6; i++) {
            for(int j = 0; j < 7; j++) {
                tablero[i][j] = ' ';
            }
        }
        
        while(true) {
            cout << " 1 2 3 4 5 6 7" << endl;
            for(int i = 0; i < 6; i++) {
                cout << "|";
                for(int j = 0; j < 7; j++) {
                    cout << tablero[i][j] << "|";
                }
                cout << endl;
            }
            cout << "---------------" << endl;
            
            ficha = (turno % 2 == 0) ? 'R' : 'A';
            cout << "jugador " << (turno % 2 + 1) << " (" << ficha << ")" << endl;
            cout << "columna: ";
            cin >> col;
            col = col - 1;
            
            if(col < 0 || col > 6) {
                cout << "columna invalida!" << endl;
                continue;
            }
            
            fila = -1;
            for(int i = 5; i >= 0; i--) {
                if(tablero[i][col] == ' ') {
                    fila = i;
                    break;
                }
            }
            
            if(fila == -1) {
                cout << "columna llena!" << endl;
                continue;
            }
            
            tablero[fila][col] = ficha;
            
            gano = 0;
            
            for(int i = 0; i < 6; i++) {
                for(int j = 0; j < 7; j++) {
                    if(tablero[i][j] != ficha) continue;
                    
                    if(j <= 3) {
                        if(tablero[i][j+1] == ficha && 
                           tablero[i][j+2] == ficha && 
                           tablero[i][j+3] == ficha) {
                            gano = 1;
                        }
                    }
                    
                    if(i <= 2) {
                        if(tablero[i+1][j] == ficha && 
                           tablero[i+2][j] == ficha && 
                           tablero[i+3][j] == ficha) {
                            gano = 1;
                        }
                    }
                }
            }
            
            if(gano == 1) {
                cout << " 1 2 3 4 5 6 7" << endl;
                for(int i = 0; i < 6; i++) {
                    cout << "|";
                    for(int j = 0; j < 7; j++) {
                        cout << tablero[i][j] << "|";
                    }
                    cout << endl;
                }
                cout << "---------------" << endl;
                cout << "jugador " << (turno % 2 + 1) << " gana!" << endl;
                break;
            }
            
            int lleno = 1;
            for(int j = 0; j < 7; j++) {
                if(tablero[0][j] == ' ') {
                    lleno = 0;
                }
            }
            
            if(lleno == 1) {
                cout << "empate!" << endl;
                break;
            }
            
            turno++;
        }
        
    }
    catch(...) {
        cout << "error en el juego" << endl;
        return 1;
    }
    
    return 0;
}