#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main(){
    string palabra;
    cout<<"Dame una palabra"<<endl;
    cin>>palabra;

    reverse(palabra.begin(), palabra.end());

    cout<<palabra<<endl;
    
    return 0;
}
