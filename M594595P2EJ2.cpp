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

void imprimirRuta(int a[5][5], int px[5][5], int py[5][5]) {
    int i = 4, j = 4;
    int rutaI[25], rutaJ[25], rutaVal[25];
    int k = 0;

    while (i != -1 && j != -1) {
        rutaI[k] = i;
        rutaJ[k] = j;
        rutaVal[k] = a[i][j];
        int ni = px[i][j];
        int nj = py[i][j];
        i = ni; j = nj;
        k++;
    }

    cout << "Ruta:" << endl;
    for (int t = k-1; t >= 0; t--) {
        cout << "(" << rutaI[t] << "," << rutaJ[t] << ") val=" << rutaVal[t];
        if (t) cout << " -> ";
    }
    cout << endl;
}

int main() {
    try {
        int a[5][5] = {
            {80, 200, 50, 30, 5},
            {40, 25, 10, 20, 30},
            {67, 110, 20, 200, 100},
            {80, 6, 45, 3, 12},
            {24, 7, 34, 15, 10}
        };

        int dp[5][5];
        int px[5][5], py[5][5];

        calcularDP(a, dp, px, py);

        cout << "Debug DP max suma por celda:" << endl;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                cout << dp[i][j];
                if (j < 4) cout << "\t";
            }
            cout << endl;
        }

        cout << "Maxima suma: " << dp[4][4] << endl;
        imprimirRuta(a, px, py);
    }
    catch (...) {
        cout << "Ocurrio un error" << endl;
    }
    return 0;
}
