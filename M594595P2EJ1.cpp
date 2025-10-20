#include <iostream>
#include <string>

using namespace std;

string cifrar(string texto){
    string resultado = "";
    for (int i = 0; i < texto.size(); i++) {
        int ascii = int(texto[i]);
        int nuevo = ascii - 100;
        while (nuevo < 32) {
            nuevo += 95; 
        }
        resultado += char(nuevo);
    }
    return resultado;
}

string decifrar(string texto){

}