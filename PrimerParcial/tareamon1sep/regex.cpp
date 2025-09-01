#include <iostream>
#include <string>
#include <regex>
using namespace std;

bool validar_regex(string email){
    if(email.size() == 0){
        throw "No ingresaste ningun valor";
    }
    regex r("^[A-Za-z0-9]+([._%+-]?[A-Za-z0-9]+)*@[A-Za-z0-9-]+(\\.[A-Za-z0-9-]+)*\\.[A-Za-z]{2,63}$");
    return regex_match(email, r);
}

int main(){
    string email;
    cout<<"Ingrese email: ";
    cin>>email;

    try{
        if(validar_regex(email)){
            cout<<"Email valido"<<endl;
        } else {
            cout<<"Email invalido"<<endl;
        }
    } catch(...){
        cout<<"Ocurrio un error"<<endl;
    }

    return 0;
}
