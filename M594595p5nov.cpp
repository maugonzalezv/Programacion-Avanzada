#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>
#include <fcntl.h>
#include <vector>

using namespace std;

const int ANCHO = 40;
const int ALTO = 15;

struct Posicion {
    int x, y;
};

vector<Posicion> vibora;
Posicion comida;
int direccion = 0;
bool hayComida = false;
time_t tiempoComida = 0;
int puntaje = 0;
bool juegoActivo = true;

void configurarTerminal() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
    
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

void restaurarTerminal() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
    
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK);
}

void limpiarPantalla() {
    cout << "\033[2J\033[H";
}

void colocarComida() {
    bool valida = false;
    while (!valida) {
        comida.x = rand() % ANCHO;
        comida.y = rand() % ALTO;
        
        valida = true;
        for (int i = 0; i < vibora.size(); i++) {
            if (vibora[i].x == comida.x && vibora[i].y == comida.y) {
                valida = false;
                break;
            }
        }
    }
    hayComida = true;
    tiempoComida = time(0);
}

void dibujarTablero() {
    limpiarPantalla();
    
    char tablero[ALTO][ANCHO];
    for (int i = 0; i < ALTO; i++) {
        for (int j = 0; j < ANCHO; j++) {
            tablero[i][j] = ' ';
        }
    }
    
    for (int i = 0; i < vibora.size(); i++) {
        if (vibora[i].y >= 0 && vibora[i].y < ALTO && 
            vibora[i].x >= 0 && vibora[i].x < ANCHO) {
            if (i == 0) {
                tablero[vibora[i].y][vibora[i].x] = 'O';
            } else {
                tablero[vibora[i].y][vibora[i].x] = 'o';
            }
        }
    }
    
    if (hayComida && comida.y >= 0 && comida.y < ALTO && 
        comida.x >= 0 && comida.x < ANCHO) {
        tablero[comida.y][comida.x] = '*';
    }
    
    for (int j = 0; j < ANCHO + 2; j++) cout << "#";
    cout << "\n";
    
    for (int i = 0; i < ALTO; i++) {
        cout << "#";
        for (int j = 0; j < ANCHO; j++) {
            cout << tablero[i][j];
        }
        cout << "#\n";
    }
    
    for (int j = 0; j < ANCHO + 2; j++) cout << "#";
    cout << "\n";
}

bool leerTecla() {
    char tecla;
    int bytes = read(STDIN_FILENO, &tecla, 1);
    
    if (bytes > 0) {
        if (tecla == 27) {
            char seq[2];
            if (read(STDIN_FILENO, &seq[0], 1) > 0 && read(STDIN_FILENO, &seq[1], 1) > 0) {
                if (seq[0] == '[') {
                    if (seq[1] == 'A' && direccion != 1) direccion = 3;
                    if (seq[1] == 'B' && direccion != 3) direccion = 1;
                    if (seq[1] == 'C' && direccion != 2) direccion = 0;
                    if (seq[1] == 'D' && direccion != 0) direccion = 2;
                }
            }
        } else if (tecla == 'q' || tecla == 'Q') {
            juegoActivo = false;
            return false;
        }
    }
    return true;
}

void moverVibora() {
    Posicion nuevaCabeza = vibora[0];
    
    if (direccion == 0) nuevaCabeza.x++;
    if (direccion == 1) nuevaCabeza.y++;
    if (direccion == 2) nuevaCabeza.x--;
    if (direccion == 3) nuevaCabeza.y--;
    
    if (nuevaCabeza.x < 0 || nuevaCabeza.x >= ANCHO || 
        nuevaCabeza.y < 0 || nuevaCabeza.y >= ALTO) {
        juegoActivo = false;
        return;
    }
    
    for (int i = 0; i < vibora.size(); i++) {
        if (vibora[i].x == nuevaCabeza.x && vibora[i].y == nuevaCabeza.y) {
            juegoActivo = false;
            return;
        }
    }
    
    vibora.insert(vibora.begin(), nuevaCabeza);
    
    if (hayComida && nuevaCabeza.x == comida.x && nuevaCabeza.y == comida.y) {
        puntaje += 10;
        hayComida = false;
    } else {
        vibora.pop_back();
    }
}

int main() {
    srand(time(0));
    configurarTerminal();
    
 
    
    Posicion inicio;
    inicio.x = ANCHO / 2;
    inicio.y = ALTO / 2;
    vibora.push_back(inicio);
    
    time_t ultimoMovimiento = time(0);
    time_t ultimaComida = time(0);
    
    while (juegoActivo) {
        time_t ahora = time(0);
        
        if (!hayComida && (ahora - ultimaComida >= 5)) {
            colocarComida();
            ultimaComida = ahora;
        }
        
        if (hayComida && (ahora - tiempoComida >= 10)) {
            hayComida = false;
        }
        
        if (!leerTecla()) {
            break;
        }
        
        if (ahora - ultimoMovimiento >= 0 || 
            (ahora * 1000000 + clock()) - (ultimoMovimiento * 1000000) >= 100000) {
            moverVibora();
            dibujarTablero();
            ultimoMovimiento = ahora;
            usleep(100000);
        }
    }
    
    restaurarTerminal();
    limpiarPantalla();
    


    cout << "  ¡Gracias por jugar!\n\n";
    
    return 0;
}