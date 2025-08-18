#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main(){
    int *x;
    double y = 100000000000000;
    try { 
        x=new int[y];
        x[0]=10;
        cout<<"Puntero: "<<(void *)x<<endl;
        delete[]x;
    }
    catch(bad_alloc&){
        cout<<"Memoria Insuficioente"<<endl;
    }

    return 0;
}