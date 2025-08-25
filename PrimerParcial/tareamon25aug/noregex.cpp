#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

bool validar(string email){
    int atCount = 0;
    int atPosition = -1;

    transform(email.begin(), email.end(), email.begin(), :: tolower);

    char final = email[email.size()-1];
    if(final> 'a' || final <'z'){
        return false;
    }

    for(int i=0;i<email.size();i++){
        if(email[i] == '.'){
            if(email[i+1]=='.'){
                return false;
            }
            if(i==0 || i==email.size()-1){
                return false;
            }
        }
        
        if(email)

    }
    return true;
    
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
