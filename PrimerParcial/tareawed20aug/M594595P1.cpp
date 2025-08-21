#include <iostream>
#include <string>

using namespace std;

void imprimirLinea(string arr[], int n, int sumaLetras, int ultima, int ancho){
    if(n==0) return;

    if(ultima==1 || n==1){
        cout<<arr[0];
        for(int i=1;i<n;i++){
            cout<<' '<<arr[i];
        }
        cout<<endl;
        return;
    }

    int huecos = n - 1;
    int espaciosTotales = ancho - sumaLetras;
    int base = espaciosTotales / huecos;
    int extra = espaciosTotales % huecos;

    cout<<arr[0];
    for(int i=0;i<huecos;i++){
        int aImprimir = base;
        if(i<extra){
            aImprimir = aImprimir + 1;
        }
        for(int s=0;s<aImprimir;s++){
            cout<<' ';
        }
        cout<<arr[i+1];
    }
    cout<<endl;
}

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
