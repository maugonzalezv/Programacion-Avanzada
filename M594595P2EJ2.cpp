#include <iostream>
using namespace std;

void calcularDP(int a[5][5], int dp[5][5], int px[5][5], int py[5][5]) {
    dp[0][0] = a[0][0];
    px[0][0] = -1; py[0][0] = -1;

    for (int j = 1; j < 5; j++) {
        dp[0][j] = dp[0][j-1] + a[0][j];
        px[0][j] = 0; py[0][j] = j-1;
    }
    for (int i = 1; i < 5; i++) {
        dp[i][0] = dp[i-1][0] + a[i][0];
        px[i][0] = i-1; py[i][0] = 0;
    }

    for (int i = 1; i < 5; i++) {
        for (int j = 1; j < 5; j++) {
            if (dp[i-1][j] > dp[i][j-1]) {
                dp[i][j] = dp[i-1][j] + a[i][j];
                px[i][j] = i-1; py[i][j] = j;
            } else {
                dp[i][j] = dp[i][j-1] + a[i][j];
                px[i][j] = i; py[i][j] = j-1;
            }
        }
    }
}

int reconstruirRuta(int a[5][5], int px[5][5], int py[5][5], int rutaVals[25]) {
    int i = 4, j = 4;
    int tmp[25];
    int k = 0;

    while (i != -1 && j != -1) {
        tmp[k] = a[i][j];
        int ni = px[i][j], nj = py[i][j];
        i = ni; j = nj;
        k++;
    }

    int n = k;
    for (int t = 0; t < n; t++) rutaVals[t] = tmp[n - 1 - t];
    return n;
}

int main() {
    try {
        int a[5][5] = {
            {80, 200, 50, 30, 5},
            {40,  25, 10, 20, 30},
            {67, 110, 20, 200,100},
            {80,   6, 45,  3, 12},
            {24,   7, 34, 15, 10}
        };

        int dp[5][5], px[5][5], py[5][5];
        calcularDP(a, dp, px, py);

        int rutaVals[25];
        int n = reconstruirRuta(a, px, py, rutaVals);

        cout << "Ruta (valores): ";
        for (int t = 0; t < n; t++) {
            cout << rutaVals[t];
            if (t < n-1) cout << " -> ";
        }
        cout << endl;

        int bestSuma = -1, bi = -1;
        for (int t = 0; t + 2 < n; t++) {
            int s = rutaVals[t] + rutaVals[t+1] + rutaVals[t+2];
            if (s > bestSuma) { bestSuma = s; bi = t; }
        }

        cout << "Mejor bloque de 3 contiguos en la ruta: "
             << rutaVals[bi] << ", " << rutaVals[bi+1] << ", " << rutaVals[bi+2] << endl;
        cout << "Suma = " << bestSuma << endl;
    }
    catch (...) {
        cout << "Ocurrio un error" << endl;
    }
    return 0;
}
