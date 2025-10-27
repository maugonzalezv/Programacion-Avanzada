#include <iostream>
using namespace std;

/*
  Programa: gato_minimax.cpp
  Objetivo: Jugar gato (3x3) contra la computadora con estrategia Minimax (árbol de decisión).
  Detalles:
    - Tablero como arreglo 1D de 9 celdas: índices [0..8], usuario ingresa [1..9].
    - 'X' = computadora, 'O' = humano (puedes elegir quién inicia).
    - Modo debug para ver evaluaciones del árbol.
    - try/catch simple para robustez de entradas.
*/

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
    int lines[8][3] = {
        {0,1,2},{3,4,5},{6,7,8}, // filas
        {0,3,6},{1,4,7},{2,5,8}, // columnas
        {0,4,8},{2,4,6}          // diagonales
    };
    for (int k = 0; k < 8; k++) {
        int a = lines[k][0], c = lines[k][1], d = lines[k][2];
        if (b[a] != ' ' && b[a] == b[c] && b[c] == b[d]) return b[a];
    }
    return ' '; // sin ganador
}

bool isFull(const char b[9]) {
    for (int i = 0; i < 9; i++) if (b[i] == ' ') return false;
    return true;
}

// Evaluación: X (compu) intenta maximizar, O (humano) minimizar.
// +10 si gana X, -10 si gana O, 0 si empate.
// Para preferir victorias tempranas/derrotas tardías, ajustamos por profundidad.
int evaluateTerminal(const char b[9], int depth) {
    char w = winner(b);
    if (w == 'X') return 10 - depth;
    if (w == 'O') return depth - 10;
    return 0; // empate
}

int minimax(char b[9], bool maximizing, int depth, bool debug) {
    char w = winner(b);
    if (w != ' ' || isFull(b)) {
        int val = evaluateTerminal(b, depth);
        if (debug) {
            cout << "[debug] depth=" << depth << " terminal ";
            if (w == ' ') cout << "(draw)";
            else cout << "(win=" << w << ")";
            cout << " -> score=" << val << endl;
        }
        return val;
    }

    if (maximizing) {
        int best = -1000000;
        for (int i = 0; i < 9; i++) {
            if (b[i] == ' ') {
                b[i] = 'X';
                int score = minimax(b, false, depth + 1, debug);
                b[i] = ' ';
                if (debug) {
                    cout << "[debug] try X@" << (i+1) << " -> score=" << score << " depth=" << depth << endl;
                }
                if (score > best) best = score;
            }
        }
        return best;
    } else {
        int best = 1000000;
        for (int i = 0; i < 9; i++) {
            if (b[i] == ' ') {
                b[i] = 'O';
                int score = minimax(b, true, depth + 1, debug);
                b[i] = ' ';
                if (debug) {
                    cout << "[debug] try O@" << (i+1) << " -> score=" << score << " depth=" << depth << endl;
                }
                if (score < best) best = score;
            }
        }
        return best;
    }
}

int bestMoveForComputer(char b[9], bool debug) {
    int bestScore = -1000000;
    int move = -1;

    // Prioriza ganar en una y bloquear en una si es posible automáticamente
    // (Minimax ya lo detecta, pero esto acelera en práctica).
    // 1) Si puedo ganar en una jugada, hazlo.
    for (int i = 0; i < 9; i++) {
        if (b[i] == ' ') {
            b[i] = 'X';
            if (winner(b) == 'X') { b[i] = ' '; return i; }
            b[i] = ' ';
        }
    }
    // 2) Si el humano puede ganar en su siguiente jugada, bloquea.
    for (int i = 0; i < 9; i++) {
        if (b[i] == ' ') {
            b[i] = 'O';
            if (winner(b) == 'O') { b[i] = ' '; return i; }
            b[i] = ' ';
        }
    }

    // 3) Usa Minimax para el resto.
    for (int i = 0; i < 9; i++) {
        if (b[i] == ' ') {
            b[i] = 'X';
            int score = minimax(b, false, 0, debug);
            b[i] = ' ';
            if (debug) {
                cout << "[debug] eval X@" << (i+1) << " => " << score << endl;
            }
            if (score > bestScore) {
                bestScore = score;
                move = i;
            }
        }
    }
    // 4) Fallback (no debería ocurrir)
    if (move == -1) {
        for (int i = 0; i < 9; i++) if (b[i] == ' ') return i;
    }
    return move;
}

int main() {
    cout << "=== GATO vs COMPUTADORA (Minimax) ===" << endl;
    cout << "Reglas: ingresa posiciones 1..9 segun el tablero mostrado." << endl;
    cout << "Computadora = X, Humano = O." << endl;

    bool debug = false;
    cout << "¿Activar modo debug? (s/n): ";
    char dbg; cin >> dbg;
    if (dbg == 's' || dbg == 'S') debug = true;

    cout << "¿Quien inicia? (c = computadora / h = humano): ";
    char inicio; cin >> inicio;

    char board[9];
    for (int i = 0; i < 9; i++) board[i] = ' ';

    try {
        bool turnComputer = (inicio == 'c' || inicio == 'C');
        while (true) {
            printBoard(board);

            // ¿Terminó?
            char w = winner(board);
            if (w == 'X') { cout << "La computadora (X) ha ganado." << endl; break; }
            if (w == 'O') { cout << "El humano (O) ha ganado." << endl; break; }
            if (isFull(board)) { cout << "Empate." << endl; break; }

            if (turnComputer) {
                int mv = bestMoveForComputer(board, debug);
                if (mv >= 0 && mv < 9 && board[mv] == ' ') {
                    board[mv] = 'X';
                    if (debug) cout << "[debug] comp juega en " << (mv+1) << endl;
                } else {
                    // Nunca debería pasar; seguridad
                    for (int i = 0; i < 9; i++) if (board[i] == ' ') { board[i] = 'X'; break; }
                }
            } else {
                cout << "Tu jugada (1..9): ";
                int pos; cin >> pos;
                if (!cin) {
                    cin.clear();
                    string basura;
                    cin >> basura;
                    cout << "Entrada invalida, intenta de nuevo." << endl;
                    continue;
                }
                if (pos < 1 || pos > 9) {
                    cout << "Rango invalido. Intenta de 1 a 9." << endl;
                    continue;
                }
                if (board[pos-1] != ' ') {
                    cout << "Esa casilla ya esta ocupada. Intenta otra." << endl;
                    continue;
                }
                board[pos-1] = 'O';
            }

            turnComputer = !turnComputer;
        }
    } catch (...) {
        cout << "Ocurrio un error inesperado. Reinicia el programa." << endl;
    }

    printBoard(board);
    cout << "Juego terminado. Gracias por jugar." << endl;
    return 0;
}
