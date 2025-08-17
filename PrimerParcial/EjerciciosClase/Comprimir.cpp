#include <iostream>
#include <string>
#include <iostream>
#include <ctype.h>

using namespace std;

string comprimir(string palabra){
    string ans;
    int contador=1;
    for(int i=0;i<palabra.size();i++){
        if(palabra[i]==palabra[i+1]){
            contador++;
        } else {
            ans += palabra[i];
            if(contador>1){
                ans += to_string(contador);
                contador = 1;
            }
        }
    }
    return ans;
}

string descomprimir(string palabra){
    string ans;
    char num;
    for(int i=0;i<palabra.size();i++){
        num = palabra[i+1];
        if(isalpha(palabra[i])){
            ans += palabra[i];
        }
        if(isdigit(num)){
            int numero = num - '0';
            for(int j=1;j<numero;j++){
                ans+=palabra[i];
            }
            i++;
        }
    }
    return ans;
}

int main(){
    string palabra;
    string ans;
    int opcion;
    cin>>palabra;
    cout<<"comprimir(1)"<<endl<<"descomprimir(2)"<<endl;
    cin>>opcion;
    if(opcion <= 0 || opcion >= 3){
        cout<<"comprimir(1)"<<endl<<"descomprimir(2)"<<endl;
        cin>>opcion;
    }
    if(opcion==1){
        ans = comprimir(palabra);
    }
    if(opcion==2){
        ans = descomprimir(palabra);
    }
    cout<<ans<<endl;
    
    return 0;
}
