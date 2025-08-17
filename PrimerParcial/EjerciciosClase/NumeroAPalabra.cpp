#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string numeroATexto(int numeroEntrada){
    string palabrasUnidades[] = {"", "uno", "dos", "tres", "cuatro", "cinco", "seis", "siete", "ocho", "nueve"};
    string palabrasEspeciales[] = {"diez", "once", "doce", "trece", "catorce", "quince"};
    string palabrasDecenas[] = {"", "", "veinte", "treinta", "cuarenta", "cincuenta", "sesenta", "setenta", "ochenta", "noventa"};
    string palabrasCentenas[] = {"", "ciento", "doscientos", "trescientos", "cuatrocientos", "quinientos",
                         "seiscientos", "setecientos", "ochocientos", "novecientos"};

    if(numeroEntrada == 0){
        return "";
    } 
    if(numeroEntrada == 100){
        return "cien";
    } 

    int centena = numeroEntrada / 100;
    int restante = numeroEntrada % 100;
    int decena = restante / 10;
    int unidad = restante % 10;

    string resultado = "";

    if(centena > 0){
        resultado += palabrasCentenas[centena];
    }

    if(restante > 0){
        if(!resultado.empty()) resultado += " ";
        if(restante < 10){
            resultado += palabrasUnidades[unidad];
        } else if(restante >= 10 && restante <= 15){
            resultado += palabrasEspeciales[restante - 10];
        } else if(restante >= 16 && restante <= 19){
            resultado += "dieci" + palabrasUnidades[unidad];
        } else if(restante == 20){
            resultado += "veinte";
        } else if(restante > 20 && restante < 30){
            resultado += "veinti" + palabrasUnidades[unidad];
        } else {
            resultado += palabrasDecenas[decena];
            if(unidad > 0){
                resultado += " y " + palabrasUnidades[unidad];
            }
        }
    }

    return resultado;
}

string quitarCerosDelInicio(string textoNumero){
    int posicion = 0;
    while(posicion + 1 < (int)textoNumero.size() && textoNumero[posicion] == '0') posicion++;
    return textoNumero.substr(posicion);
}

int main(){
    string numeroIngresado;
    cin >> numeroIngresado;

    string parteNormales, parteMiles, parteMillones;

    int longitudNumero = (int)numeroIngresado.length();

    if(longitudNumero <= 3){
        parteNormales = numeroIngresado;
    } else if(longitudNumero <= 6){
        parteNormales = numeroIngresado.substr(longitudNumero - 3);
        parteMiles = numeroIngresado.substr(0, longitudNumero - 3);
    } else {
        parteNormales = numeroIngresado.substr(longitudNumero - 3);
        parteMiles = numeroIngresado.substr(longitudNumero - 6, 3);
        parteMillones = numeroIngresado.substr(0, longitudNumero - 6);
    }

    if(!parteMillones.empty()) parteMillones = quitarCerosDelInicio(parteMillones);
    if(!parteMiles.empty()) parteMiles = quitarCerosDelInicio(parteMiles);
    if(!parteNormales.empty()) parteNormales = quitarCerosDelInicio(parteNormales);

    int numeroMillones = (parteMillones.empty() ? 0 : stoi(parteMillones));
    int numeroMiles    = (parteMiles.empty()    ? 0 : stoi(parteMiles));
    int numeroNormales = (parteNormales.empty() ? 0 : stoi(parteNormales));

    if(numeroMillones == 0 && numeroMiles == 0 && numeroNormales == 0){
        cout << "cero"<<endl;
        return 0;
    }

    string textoFinal = "";

    if(numeroMillones > 0){
        if(numeroMillones == 1){
            textoFinal += "un millon";
        } else {
            textoFinal += numeroATexto(numeroMillones) + " millones";
        }
    }

    if(numeroMiles > 0){
        if(!textoFinal.empty()) textoFinal += " ";
        if(numeroMiles == 1){
            textoFinal += "mil"; 
        } else {
            textoFinal += numeroATexto(numeroMiles) + " mil";
        }
    }

    if(numeroNormales > 0){
        if(!textoFinal.empty()) textoFinal += " ";
        textoFinal += numeroATexto(numeroNormales);
    }

    cout << textoFinal <<endl;
    return 0;
}