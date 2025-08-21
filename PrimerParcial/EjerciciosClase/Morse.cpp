#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string morseCode[] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
    "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-",
    "...-", ".--", "-..-", "-.--", "--.."
};

int main() {
    string palabra;
    cout << "Dame una palabra: ";
    cin >> palabra;
    transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);
    string morse = "";
    for (int i = 0; i<palabra.size(); i++) {
        if(palabra[i] >= 'a' && palabra[i] <= 'z') {
            int j = palabra[i] - 'a';
            morse += morseCode[j];
            morse += " ";
        }
        
    }

    cout << morse << endl;

    return 0;
}