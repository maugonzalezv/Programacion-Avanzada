#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main(){
    string texto;
    string empresa = "";
    string correo = "";
    string cp = "";

    cout<<"Inserte el texto: "<<endl;
    getline(cin, texto);

    try { 
        if(texto.size()==0){
            throw "No hay texto";
        }

        regex rEmpresa("empresa\\s*\"([^\"]+)\"");
        regex rCorreo("[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,63}");
        regex rCP("CP\\s*(\\d{5})");

    } catch (...) {

    }

}