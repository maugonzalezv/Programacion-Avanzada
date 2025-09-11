#include <iostream>
#include <cmath>
using namespace std;

bool esPrimo(int n, int divisor =2) {
    if(n < 2) {
        return false;
    }
    if(divisor>n/2){
        return true;
    }
    if(n%divisor==0){
        return false;
    }
    return esPrimo(n,divisor+1);
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
