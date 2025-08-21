#include <iostream>
#include <string>

using namespace std;

int main(){
    int mes, dia, anio;
    string meses[13] = {"", "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
                        "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};

    cout<<"Dame la fecha en formato mm/dd/aaaa"<<endl;
    cin>>mes>>dia>>anio;

    cout<<mes<<"/"<<dia<<"/"<<anio<<endl;
    cout<<meses[mes]<<" "<<dia<<", "<<anio<<endl;
    cout<<dia<<" de "<<meses[mes]<<" de "<<anio<<endl;

    return 0;
}
