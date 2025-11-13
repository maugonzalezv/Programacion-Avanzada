#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <termios.h>
using namespace std;

int tablero[4][4];
int vx, vy;

void inicializar() {
    int nums[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};
    
    for(int i = 0; i < 100; i++) {
        int a = rand() % 16;
        int b = rand() % 16;
        int temp = nums[a];
        nums[a] = nums[b];
        nums[b] = temp;
    }
    
    int k = 0;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            tablero[i][j] = nums[k];
            if(nums[k] == 0) {
                vx = i;
                vy = j;
            }
            k++;
        }
    }
}

void dibujar() {
    system("clear");
    cout << "\n  Juego del 15 - Mueve con W/A/S/D\n\n";
    
    for(int i = 0; i < 4; i++) {
        cout << "  +----+----+----+----+\n";
        cout << "  |";
        for(int j = 0; j < 4; j++) {
            if(tablero[i][j] == 0) {
                cout << "    |";
            } else {
                if(tablero[i][j] < 10) {
                    cout << "  " << tablero[i][j] << " |";
                } else {
                    cout << " " << tablero[i][j] << " |";
                }
            }
        }
        cout << "\n";
    }
    cout << "  +----+----+----+----+\n";
}

char leerTecla() {
    struct termios old, nuevo;
    tcgetattr(0, &old);
    nuevo = old;
    nuevo.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &nuevo);
    
    char c = getchar();
    
    tcsetattr(0, TCSANOW, &old);
    return c;
}

void mover(char tecla) {
    int nx = vx;
    int ny = vy;
    
    if(tecla == 'w' || tecla == 'W') {
        nx = vx + 1;
    } else if(tecla == 's' || tecla == 'S') {
        nx = vx - 1;
    } else if(tecla == 'a' || tecla == 'A') {
        ny = vy + 1;
    } else if(tecla == 'd' || tecla == 'D') {
        ny = vy - 1;
    }
    
    if(nx >= 0 && nx < 4 && ny >= 0 && ny < 4) {
        tablero[vx][vy] = tablero[nx][ny];
        tablero[nx][ny] = 0;
        vx = nx;
        vy = ny;
    }
}

bool ganaste() {
    int esperado = 1;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(i == 3 && j == 3) {
                if(tablero[i][j] != 0) return false;
            } else {
                if(tablero[i][j] != esperado) return false;
                esperado++;
            }
        }
    }
    return true;
}

int main() {
    srand(time(0));
    
    inicializar();
    
    while(true) {
        dibujar();
        
        if(ganaste()) {
            cout << "\n  ganaste\n\n";
            break;
        }
        
        cout << "\n  presiona Q para salir\n";
        
        char tecla = leerTecla();
        
        if(tecla == 'q' || tecla == 'Q') {
            break;
        }
        
        mover(tecla);
    }
    
    return 0;
}