#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string convertirTresCifras(int n){
    string unidades[] = {"", "uno", "dos", "tres", "cuatro", "cinco", "seis", "siete", "ocho", "nueve"};
    string decenas10_15[] = {"diez", "once", "doce", "trece", "catorce", "quince"};
    string decenasMultiplo[] = {"", "", "veinte", "treinta", "cuarenta", "cincuenta", "sesenta", "setenta", "ochenta", "noventa"};
    string centenas[] = {"", "ciento", "doscientos", "trescientos", "cuatrocientos", "quinientos",
                         "seiscientos", "setecientos", "ochocientos", "novecientos"};

    if(n == 0){
        return "";
    } 
    if(n == 100){
        return "cien";
    } 

    int c = n / 100;
    int r = n % 100;
    int d = r / 10;
    int u = r % 10;

    string texto = "";

    if(c > 0){
        texto += centenas[c];
    }

    if(r > 0){
        if(!texto.empty()) texto += " ";
        if(r < 10){
            texto += unidades[u];
        } else if(r >= 10 && r <= 15){
            texto += decenas10_15[r - 10];
        } else if(r >= 16 && r <= 19){
            texto += "dieci" + unidades[u];
        } else if(r == 20){
            texto += "veinte";
        } else if(r > 20 && r < 30){
            texto += "veinti" + unidades[u];
        } else {
            texto += decenasMultiplo[d];
            if(u > 0){
                texto += " y " + unidades[u];
            }
        }
    }

    return texto;
}

int main(){
    string numero;
    cin >> numero;

    string normales, miles, millones;

    int len = (int)numero.length();

    if(len <= 3){
        normales = numero;
    } else if(len <= 6){
        normales = numero.substr(len - 3);
        miles = numero.substr(0, len - 3);
    } else {
        normales = numero.substr(len - 3);
        miles = numero.substr(len - 6, 3);
        millones = numero.substr(0, len - 6);
    }

    auto limpia = [](string s){
        int p = 0;
        while(p + 1 < (int)s.size() && s[p] == '0') p++;
        return s.substr(p);
    };

    if(!millones.empty()) millones = limpia(millones);
    if(!miles.empty()) miles = limpia(miles);
    if(!normales.empty()) normales = limpia(normales);

    int nMillones = (millones.empty() ? 0 : stoi(millones));
    int nMiles    = (miles.empty()    ? 0 : stoi(miles));
    int nNormales = (normales.empty() ? 0 : stoi(normales));

    if(nMillones == 0 && nMiles == 0 && nNormales == 0){
        cout << "cero"<<endl;
        return 0;
    }

    string salida = "";

    if(nMillones > 0){
        if(nMillones == 1){
            salida += "un millon";
        } else {
            salida += convertirTresCifras(nMillones) + " millones";
        }
    }

    if(nMiles > 0){
        if(!salida.empty()) salida += " ";
        if(nMiles == 1){
            salida += "mil"; 
        } else {
            salida += convertirTresCifras(nMiles) + " mil";
        }
    }

    if(nNormales > 0){
        if(!salida.empty()) salida += " ";
        salida += convertirTresCifras(nNormales);
    }

    cout << salida <<endl;
    return 0;
}
