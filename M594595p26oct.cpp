#include <iostream>
using namespace std;

// Tablero 1D con 9 celdas: índices 0..8, usuario ingresa 1..9
void printBoard(const char b[9]) {
    cout << endl;
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            int i = r * 3 + c;
            cout << " " << (b[i] == ' ' ? char('1' + i) : b[i]) << " ";
            if (c < 2) cout << "|";
        }
        cout << endl;
        if (r < 2) cout << "---+---+---" << endl;
    }
    cout << endl;
}

char winner(const char b[9]) {
    int L[8][3] = {
        {0,1,2},{3,4,5},{6,7,8},
        {0,3,6},{1,4,7},{2,5,8},
        {0,4,8},{2,4,6}
    };
    for (int k = 0; k < 8; k++) {
        int a=L[k][0], c=L[k][1], d=L[k][2];
        if (b[a] != ' ' && b[a] == b[c] && b[c] == b[d]) return b[a];
    }
    return ' ';
}

bool isFull(const char b[9]) {
    for (int i = 0; i < 9; i++) if (b[i] == ' ') return false;
    return true;
}

// Si jugador 'p' puede ganar en una jugada, devuelve esa casilla; si no, -1
int oneMoveWin(char b[9], char p) {
    int L[8][3] = {
        {0,1,2},{3,4,5},{6,7,8},
        {0,3,6},{1,4,7},{2,5,8},
        {0,4,8},{2,4,6}
    };
    for (int k = 0; k < 8; k++) {
        int a=L[k][0], c=L[k][1], d=L[k][2];
        int cntP = (b[a]==p) + (b[c]==p) + (b[d]==p);
        int cntE = (b[a]==' ') + (b[c]==' ') + (b[d]==' ');
        if (cntP==2 && cntE==1) {
            if (b[a]==' ') return a;
            if (b[c]==' ') return c;
            if (b[d]==' ') return d;
        }
    }
    return -1;
}

// Reglas simples para la PC (X): ganar, bloquear, centro, esquinas, lados
int computerMove(char b[9]) {
    // 1) Ganar en una
    int m = oneMoveWin(b, 'X');
    if (m != -1) return m;
    // 2) Bloquear al humano (O)
    m = oneMoveWin(b, 'O');
    if (m != -1) return m;
    // 3) Centro
    if (b[4] == ' ') return 4;
    // 4) Esquinas
    int corners[4] = {0,2,6,8};
    for (int i = 0; i < 4; i++) if (b[corners[i]]==' ') return corners[i];
    // 5) Lados
    int sides[4] = {1,3,5,7};
    for (int i = 0; i < 4; i++) if (b[sides[i]]==' ') return sides[i];
    // 6) Fallback (no debería)
    for (int i = 0; i < 9; i++) if (b[i]==' ') return i;
    return -1;
}

int main() {
    cout << "=== GATO SIMPLE (PC = X, Humano = O) ===" << endl;

    char b[9];
    for (int i = 0; i < 9; i++) b[i] = ' ';

    // Puedes cambiar quien empieza: 'c' compu, 'h' humano.
    char inicio;
    cout << "¿Quien inicia? (c/h): ";
    cin >> inicio;
    bool turnComputer = (inicio=='c' || inicio=='C');

    try {
        while (true) {
            printBoard(b);

            char w = winner(b);
            if (w == 'X') { cout << "Gana la computadora (X)." << endl; break; }
            if (w == 'O') { cout << "Gana el humano (O)." << endl; break; }
            if (isFull(b)) { cout << "Empate." << endl; break; }

            if (turnComputer) {
                int mv = computerMove(b);
                if (mv >= 0 && mv < 9 && b[mv]==' ') b[mv] = 'X';
            } else {
                cout << "Tu jugada (1..9): ";
                int pos; cin >> pos;
                if (!cin) {
                    cin.clear();
                    string basura; cin >> basura;
                    cout << "Entrada invalida." << endl;
                    continue;
                }
                if (pos < 1 || pos > 9) { cout << "Rango invalido." << endl; continue; }
                if (b[pos-1] != ' ') { cout << "Ocupado, elige otra." << endl; continue; }
                b[pos-1] = 'O';
            }
            turnComputer = !turnComputer;
        }
    } catch (...) {
        cout << "Error inesperado." << endl;
    }

    printBoard(b);
    cout << "Fin del juego." << endl;
    return 0;
}
