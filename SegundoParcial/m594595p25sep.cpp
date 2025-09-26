#include <iostream>
#include <string>
#include <openssl/ssl.h>
#include <openssl/rand.h>
using namespace std;

int valor(char c) {
    return c - 'A';
}

char rotar(char c, int r) {
    int x = valor(c);
    x = (x + (r % 26) + 26) % 26;
    return static_cast<char>('A' + x);
}

int main() {
    try {
        SSL_library_init();
        RAND_poll();

        int k;
        cin >> k;

        for(int caso = 0; caso < k; caso++) {
            string s;
            cin >> s;

            int n = s.size();
            int m = n / 2;

            string a = s.substr(0, m);
            string b = s.substr(m);

            long long sumaA = 0;
            for(int i = 0; i < m; i++) {
                sumaA += valor(a[i]);
            }
            int rotA = sumaA % 26;

            long long sumaB = 0;
            for(int i = 0; i < m; i++) {
                sumaB += valor(b[i]);
            }
            int rotB = sumaB % 26;

            for(int i = 0; i < m; i++) {
                a[i] = rotar(a[i], rotA);
                b[i] = rotar(b[i], rotB);
            }

            for(int i = 0; i < m; i++) {
                int r = valor(b[i]);
                a[i] = rotar(a[i], r);
            }

            cout << a << endl;
        }
    }
    catch(...) {
        cout << "Error" << endl;
    }

    return 0;
}
