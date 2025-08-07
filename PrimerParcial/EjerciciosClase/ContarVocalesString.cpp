#include <iostream>
#include <string>

using namespace std;

int main(){
    string palabra;
    int vocales=0;
    cout<<"Dame una palabra"<<endl;
    cin>>palabra;

    for(int i=0;i<palabra.size();i++){
        if(palabra[i]=='a' || palabra[i]=='e' || palabra[i]=='i' || palabra[i]=='o' || palabra[i]=='u' ){
            vocales++;
        }
    }
    cout<<vocales<<endl;
    return 0;
}
