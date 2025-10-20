// Astar_10x10_simple.cpp
// A*: ruta más corta en 10x10 con 4 direcciones.
// Entradas: inicio (x y), meta (x y), 4 obstáculos (x y), factor h, debug (s/n).
// Salida: tablero con S, T, #, *, .  y costos básicos.

#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include <stdexcept>
#include <cmath>
using namespace std;

int filas = 10;
int columnas = 10;

bool enRango(int x, int y) {
    return x >= 0 && x < filas && y >= 0 && y < columnas;
}

double heuristicaManhattan(int x, int y, int gx, int gy, double factorH) {
    return factorH * (double)(abs(x - gx) + abs(y - gy));
}

void imprimirTablero(char tablero[10][10]) {
    cout << endl << "Tablero (10 x 10):" << endl << endl;
    cout << "    ";
    for (int j = 0; j < 10; j++) cout << j << ' ';
    cout << endl;
    cout << "   ---------------------" << endl;
    for (int i = 0; i < 10; i++) {
        cout << i << " | ";
        for (int j = 0; j < 10; j++) {
            cout << tablero[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl << "Leyenda: S=inicio, T=meta, #=obstaculo, *=ruta, .=explorado" << endl;
}

void reconstruirRuta(int padreX[10][10], int padreY[10][10],
                     int sx, int sy, int gx, int gy, char tablero[10][10]) {
    int cx = gx, cy = gy;
    while (!(cx == sx && cy == sy)) {
        if (tablero[cx][cy] == ' ' || tablero[cx][cy] == '.') tablero[cx][cy] = '*';
        int px = padreX[cx][cy];
        int py = padreY[cx][cy];
        if (px == -1 && py == -1) break;
        cx = px; cy = py;
    }
    tablero[sx][sy] = 'S';
    tablero[gx][gy] = 'T';
}

int main() {
    try {
        char tablero[10][10];
        int obst[10][10];
        int cerrado[10][10];
        double gscore[10][10];
        int padreX[10][10];
        int padreY[10][10];

        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                tablero[i][j] = ' ';
                obst[i][j] = 0;
                cerrado[i][j] = 0;
                gscore[i][j] = 1e18;
                padreX[i][j] = -1;
                padreY[i][j] = -1;
            }
        }

        int sx, sy, gx, gy;
        cout << "Ingrese nodo inicio (x y) en rango [0,9]: ";
        cin >> sx >> sy;
        cout << "Ingrese nodo meta   (x y) en rango [0,9]: ";
        cin >> gx >> gy;

        cout << "Ingrese 4 obstaculos (x y) en rango [0,9], uno por linea:" << endl;
        for (int k = 0; k < 4; k++) {
            int ox, oy;
            cin >> ox >> oy;
            if (!enRango(ox, oy)) throw runtime_error("Obstaculo fuera de rango.");
            obst[ox][oy] = 1;
        }

        double factorH;
        cout << "Ingrese factor que altera la heuristica h (ej. 1.0, 1.3, 2.0): ";
        cin >> factorH;

        char debugChar;
        bool debug = false;
        cout << "Debug? (s/n): ";
        cin >> debugChar;
        if (debugChar == 's' || debugChar == 'S') debug = true;

        if (!enRango(sx, sy) || !enRango(gx, gy)) {
            throw runtime_error("Inicio o meta fuera de rango.");
        }
        if (sx == gx && sy == gy) throw runtime_error("Inicio y meta no pueden ser iguales.");
        if (obst[sx][sy] || obst[gx][gy]) throw runtime_error("Obstaculo en inicio o meta.");

        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
                if (obst[i][j]) tablero[i][j] = '#';

        tablero[sx][sy] = 'S';
        tablero[gx][gy] = 'T';

        // A*: usamos priority_queue de (f, id) donde id = x*10 + y
        priority_queue< pair<double,int>, vector<pair<double,int> >, greater<pair<double,int> > > abiertos;

        gscore[sx][sy] = 0.0;
        double h0 = heuristicaManhattan(sx, sy, gx, gy, factorH);
        abiertos.push(make_pair(0.0 + h0, sx * 10 + sy));

        int dx[4] = {-1, 1, 0, 0};
        int dy[4] = {0, 0, -1, 1};

        bool encontrada = false;

        while (!abiertos.empty()) {
            pair<double,int> top = abiertos.top();
            abiertos.pop();

            int id = top.second;
            int x = id / 10;
            int y = id % 10;

            if (cerrado[x][y]) continue;
            cerrado[x][y] = 1;

            double gActual = gscore[x][y];
            double hActual = heuristicaManhattan(x, y, gx, gy, factorH);
            double fActual = gActual + hActual;

            if (debug) {
                cout << "[DEBUG] Expande (" << x << "," << y
                     << ") g=" << gActual << " h=" << hActual
                     << " f=" << fActual << endl;
            }

            if (x == gx && y == gy) {
                encontrada = true;
                break;
            }

            if (tablero[x][y] == ' ') tablero[x][y] = '.';

            for (int k = 0; k < 4; k++) {
                int nx = x + dx[k];
                int ny = y + dy[k];
                if (!enRango(nx, ny)) continue;
                if (obst[nx][ny]) continue;
                if (cerrado[nx][ny]) continue;

                double nuevoG = gActual + 1.0; // movimiento unitario
                if (nuevoG < gscore[nx][ny]) {
                    gscore[nx][ny] = nuevoG;
                    padreX[nx][ny] = x;
                    padreY[nx][ny] = y;
                    double h = heuristicaManhattan(nx, ny, gx, gy, factorH);
                    double f = nuevoG + h;
                    abiertos.push(make_pair(f, nx * 10 + ny));

                    if (debug) {
                        cout << "[DEBUG]   Vecino (" << nx << "," << ny
                             << ") g=" << nuevoG << " h=" << h
                             << " f=" << f << endl;
                    }
                }
            }
        }

        if (!encontrada) {
            cout << endl << "No existe ruta posible." << endl;
            imprimirTablero(tablero);
            return 0;
        }

        reconstruirRuta(padreX, padreY, sx, sy, gx, gy, tablero);

        cout << endl << "Ruta encontrada con A*." << endl;
        cout << "Costo total (g) = " << gscore[gx][gy] << endl;
        cout << "Heuristica inicio (h) = " << h0 << "  (factor = " << factorH << ")" << endl;
        cout << "f(inicio) = " << (0.0 + h0) << endl;

        imprimirTablero(tablero);
    }
    catch (const exception& e) {
        cout << endl << "[ERROR] " << e.what() << endl;
        cout << "Revisa rangos [0,9], que inicio/meta no coincidan y que los obstaculos no caigan en inicio/meta." << endl;
    }
    catch (...) {
        cout << endl << "[ERROR] Ocurrio un error no controlado." << endl;
    }

    return 0;
}
