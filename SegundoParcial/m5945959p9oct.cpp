#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool buscarPalabra(char sopa[][15], int filas, int columnas, string palabra, int fila, int col) {
    int dx[8] = {-1,-1,-1,0,0,1,1,1};
    int dy[8] = {-1,0,1,-1,1,-1,0,1};
    int len = palabra.size();

    for(int dir = 0; dir < 8; dir++) {
        int k;
        int nuevaFila = fila + dx[dir];
        int nuevaCol = col + dy[dir];

        for(k = 1; k < len; k++) {
            if(nuevaFila < 0 || nuevaFila >= filas || nuevaCol < 0 || nuevaCol >= columnas) {
                break;
            }
            if(sopa[nuevaFila][nuevaCol] != palabra[k]) {
                break;
            }
            nuevaFila += dx[dir];
            nuevaCol += dy[dir];
        }

        if(k == len) {
            cout << "palabra encontrada " << dir << " desde (" << fila << "," << col << ")" << endl;
            return true;
        }
    }
    return false;
}

void resolverSopa(char sopa[][15], int filas, int columnas, vector<string> palabras) {
    for(int p = 0; p < palabras.size(); p++) {
        string palabra = palabras[p];
        bool encontrada = false;
        cout << "Buscando: " << palabra << endl;

        for(int i = 0; i < filas; i++) {
            for(int j = 0; j < columnas; j++) {
                if(sopa[i][j] == palabra[0]) {
                    if(buscarPalabra(sopa, filas, columnas, palabra, i, j)) {
                        cout  << palabra << " encontrada en (" << i << "," << j << ")" << endl;
                        encontrada = true;
                    }
                }
            }
        }

        if(!encontrada) {
            cout << palabra << " no encontrada" << endl;
        }
        cout << endl;
    }
}

int main() {
    try {
        char sopa[15][15] = {
            {'m','c','u','c','a','r','a','c','h','a','l','a','p','m','i'},
            {'o','f','r','a','i','l','e','c','i','l','l','o','p','o','t'},
            {'s','a','m','a','l','l','i','n','i','h','c','o','c','n','p'},
            {'c','w','o','a','d','u','c','a','r','r','a','b','o','o','o'},
            {'a','s','a','l','t','a','m','o','n','t','e','s','s','c','l'},
            {'o','r','i','n','o','c','e','r','o','n','t','e','n','o','l'},
            {'j','e','d','e','l','e','f','a','n','t','e','i','a','y','o'},
            {'a','t','a','n','a','r','a','j','i','t','r','a','g','a','l'},
            {'b','n','l','r','a','c','o','d','o','r','n','i','z','m','l'},
            {'a','e','l','m','a','m','u','l','o','i','o','r','c','a','i'},
            {'r','i','i','e','b','a','t','l','r','a','t','a','c','a','d'},
            {'a','p','l','r','u','h','i','l','e','c','h','u','z','a','a'},
            {'c','r','o','s','c','n','a','p','a','r','e','n','o','u','m'},
            {'s','e','p','a','r','g','r','c','a','s','t','o','r','g','r'},
            {'e','s','c','o','a','l','l','i','h','c','n','i','h','c','a'}
        };

        int filas = 15;
        int columnas = 15;
        vector<string> palabras;
        int n;

        cout << "Ingrese la cantidad de palabras a buscar: ";
        cin >> n;
        cout << endl;

        for(int i = 0; i < n; i++) {
            string palabra;
            cout << "Ingrese palabra " << i+1 << ": ";
            cin >> palabra;
            palabras.push_back(palabra);
        }

        cout << endl << "DEBUG: Iniciando busqueda en sopa de letras..." << endl;
        resolverSopa(sopa, filas, columnas, palabras);

    } catch(exception &e) {
        cout << "Error: " << e.what() << endl;
    }

    cout << endl << "FIN" << endl;
    return 0;
}
