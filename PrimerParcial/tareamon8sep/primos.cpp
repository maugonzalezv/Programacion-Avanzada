#include <iostream>
#include <cmath>
using namespace std;

bool esPrimo(int n) {
    if(n < 2) {
        return false;
    }
    for(int i = 2; i <= sqrt(n); i++) {
        if(n % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    try {
        int numero;
        cout << "Dame un numero: ";
        cin >> numero;

        if(cin.fail() || numero < 2) {
            throw 1;
        }

        cout << "Numeros primos entre 1 y " << numero << ":" << endl;
        for(int i = 2; i <= numero; i++) {
            if(esPrimo(i)) {
                cout << i << endl;
            }
        }
    }
    catch(...) {
        cout << "Error" << endl;
    }

    return 0;
}
