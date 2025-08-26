#include <iostream>
#include <string>
using namespace std;

bool validar(string email){
    if(email.size() == 0){
        throw "No ingresaste ningun valor";
    }

    for(int i=0; i<email.size(); i++){
        if(email[i] >= 'A' && email[i] <= 'Z'){
            email[i] = email[i] - 'A' + 'a';
        }
    }

    char final = email[email.size()-1];
    if(final < 'a' || final > 'z'){
        return false;
    }
    if(email[email.size()-1] == '.'){
        return false;
    }
    if(email[0] == '.') return false;
    for(int i=0; i<email.size()-1; i++){
        if(email[i] == '.' && email[i+1] == '.'){
            return false;
        }
    }

    int atCount = 0;
    int atPos = -1;
    for(int i=0; i<email.size(); i++){
        if(email[i] == '@'){
            atCount++;
            atPos = i;
            if(atCount > 1) return false;
        }
    }

    if(atCount != 1) return false;
    if(atPos == 0 || atPos == email.size()-1) return false;
    if(email[atPos-1] == '.') return false;
    if(email[atPos+1] == '.') return false;

    bool puntoDespues = false;
    for(int i=atPos+1; i<email.size(); i++){
        if(email[i] == '.'){
            puntoDespues = true;
            break;
        }
    }
    if(puntoDespues == false) return false;

    return true;
}

int main(){
    string email;
    cout<<"Ingrese email: ";
    cin>>email;

    try{
        if(validar(email)){
            cout<<"Email valido"<<endl;
        } else {
            cout<<"Email invalido"<<endl;
        }
    } catch(...){
        cout<<"Ocurrio un error"<<endl;
    }

    return 0;
}
