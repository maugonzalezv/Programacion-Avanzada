#include <iostream>
using namespace std;

int main() {
    try {
        int a[5][5] = {
            {80, 200, 50, 30, 5},
            {40,  25, 10, 20, 30},
            {67, 110, 20, 200,100},
            {80,   6, 45,  3, 12},
            {24,   7, 34, 15, 10}
        };

        int mejorSuma = -1;
        int v1 = 0, v2 = 0, v3 = 0;

        // Recorremos toda la matriz buscando el bloque de 3 con suma más alta
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {

                // Tomar el valor actual y los dos siguientes en la misma columna (si hay espacio)
                if (i + 2 < 5) {
                    int suma = a[i][j] + a[i+1][j] + a[i+2][j];
                    if (suma > mejorSuma) {
                        mejorSuma = suma;
                        v1 = a[i][j];
                        v2 = a[i+1][j];
                        v3 = a[i+2][j];
                    }
                }

                // Tomar el valor actual y los dos siguientes en la misma fila (si hay espacio)
                if (j + 2 < 5) {
                    int suma = a[i][j] + a[i][j+1] + a[i][j+2];
                    if (suma > mejorSuma) {
                        mejorSuma = suma;
                        v1 = a[i][j];
                        v2 = a[i][j+1];
                        v3 = a[i][j+2];
                    }
                }
            }
        }

        cout << "Mejor combinacion de 3 valores: " 
             << v1 << ", " << v2 << ", " << v3 << endl;
        cout << "Suma = " << mejorSuma << endl;
    }
    catch (...) {
        cout << "Ocurrio un error" << endl;
    }

    return 0;
}
