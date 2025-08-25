#include <iostream>
#include <string>

using namespace std;

int main(){
    int ancho = 65;
    string palabra;
    string linea[200];
    int n = 0;
    int sumaLetras = 0;

    while(cin>>palabra){
        int len = (int)palabra.size();
        if(n==0){
            linea[0]=palabra;
            n=1;
            sumaLetras=len;
        } else {
            int largoConNueva = sumaLetras + n + len;
            if(largoConNueva<=ancho){
                linea[n]=palabra;
                n=n+1;
                sumaLetras=sumaLetras+len;
            } else {
                imprimirLinea(linea, n, sumaLetras, 0, ancho);
                linea[0]=palabra;
                n=1;
                sumaLetras=len;
            }
        }
    }

    imprimirLinea(linea, n, sumaLetras, 1, ancho);
    return 0;
}
