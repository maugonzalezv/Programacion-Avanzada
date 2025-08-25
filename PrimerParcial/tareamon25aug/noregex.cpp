#include <iostream>
#include <string>

using namespace std;

bool validar(string email){
    int atCount = 0;
    int atPosition = 0;
    int dotCount = 0;

    for(int i=0;i<email.size();i++){
        if(email[i]=='@'){
            atCount++;
        }
        if(atCount>1){
            return false;
        }

    }
    
}

int main(){
    string email;
    cout<<"Ingrese email: ";
    cin>>email;

    if(validar(email)){
        cout<<"Email valido"<<endl;
    } else {
        cout<<"Email invalido"<<endl;
    }   

    return 0;
}
