#include <iostream>
#include <string>
#include <queue>
using namespace std;

struct Nodo {
    int valor;
    Nodo* izq;
    Nodo* der;
    bool asignado;
};

Nodo* crearNodo() {
    Nodo* n = new Nodo();
    n->valor = 0;
    n->izq = 0;
    n->der = 0;
    n->asignado = false;
    return n;
}

bool insertar(Nodo* raiz, int valor, string ruta) {
    Nodo* actual = raiz;
    
    for(int i = 0; i < ruta.length(); i++) {
        if(ruta[i] == 'L') {
            if(actual->izq == 0) {
                actual->izq = crearNodo();
            }
            actual = actual->izq;
        } else {
            if(actual->der == 0) {
                actual->der = crearNodo();
            }
            actual = actual->der;
        }
    }
    
    if(actual->asignado) {
        return false;
    }
    
    actual->valor = valor;
    actual->asignado = true;
    return true;
}

bool esCompleto(Nodo* raiz) {
    if(raiz == 0) return true;
    
    queue<Nodo*> q;
    q.push(raiz);
    
    while(!q.empty()) {
        Nodo* actual = q.front();
        q.pop();
        
        if(!actual->asignado) {
            return false;
        }
        
        if(actual->izq != 0) {
            q.push(actual->izq);
        }
        if(actual->der != 0) {
            q.push(actual->der);
        }
    }
    
    return true;
}

void imprimirBFS(Nodo* raiz) {
    queue<Nodo*> q;
    q.push(raiz);
    bool primero = true;
    
    while(!q.empty()) {
        Nodo* actual = q.front();
        q.pop();
        
        if(!primero) {
            cout << " ";
        }
        cout << actual->valor;
        primero = false;
        
        if(actual->izq != 0) {
            q.push(actual->izq);
        }
        if(actual->der != 0) {
            q.push(actual->der);
        }
    }
    cout << endl;
}

int main() {
    int k;
    cin >> k;
    cin.ignore();
    
    for(int t = 0; t < k; t++) {
        string linea;
        getline(cin, linea);
        
        Nodo* raiz = crearNodo();
        bool valido = true;
        
        int i = 0;
        while(i < linea.length()) {
            if(linea[i] == '(') {
                i++;
                
                if(linea[i] == ')') {
                    break;
                }
                
                string numStr = "";
                while(linea[i] != ',') {
                    if(linea[i] != ' ') {
                        numStr += linea[i];
                    }
                    i++;
                }
                
                i++;
                
                string ruta = "";
                while(linea[i] != ')') {
                    if(linea[i] != ' ') {
                        ruta += linea[i];
                    }
                    i++;
                }
                
                int valor = 0;
                for(int j = 0; j < numStr.length(); j++) {
                    valor = valor * 10 + (numStr[j] - '0');
                }
                
                if(!insertar(raiz, valor, ruta)) {
                    valido = false;
                }
                
                i++;
            } else {
                i++;
            }
        }
        
        if(valido && esCompleto(raiz)) {
            imprimirBFS(raiz);
        } else {
            cout << "INCOMPLETE" << endl;
        }
    }
    
    return 0;
}