#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main(){
    double cantidad;
    cout<<"Dame la cantidad del cheque"<<endl;
    cin>>cantidad;

    string numero = to_string(cantidad);
    int punto = numero.find('.');
    if(punto != -1){
        numero = numero.substr(0,punto+3);
    }

    int espacios = 8 - numero.size();
    for(int i=0;i<espacios;i++){
        cout<<"*";
    }
    cout<<numero<<endl;

    return 0;
}
