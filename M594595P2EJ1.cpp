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
    string resultado = "";
    for (int i = 0; i < texto.size(); i++) {
        int ascii = int(texto[i]);
        int nuevo = ascii + 100;
        while (nuevo > 126) {
            nuevo -= 95; 
        }
        resultado += char(nuevo);
    }
    return resultado;
}

int main(){
    try{
        string texto;
        int opcion;

        cout << "1 cifrar" << endl;
        cout << "2 decifrar" << endl;
        cin >> opcion;

        cout << "Ingresa el texto: ";
        getline(cin, texto);

        cout << "Debug: texto original -> " << texto << endl;

        if (opcion == 1) {
            string cifrado = cifrar(texto);
            cout << "Texto cifrado: " << cifrado << endl;
        } 
        else if (opcion == 2) {
            string decifrado = decifrar(texto);
            cout << "Texto decifrado: " << decifrado << endl;
        } 
        else {
            cout << "Opcion no valida" << endl;
        }
    }
    catch(...){
        cout<<"Ocurrio un error"<<endl;
    }
    return 0;
}