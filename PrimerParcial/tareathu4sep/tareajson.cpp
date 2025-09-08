#include <iostream>
#include <fstream>
#include <string>
#include <regex>
using namespace std;

string leerArchivoComoString(const string& ruta){
    ifstream in(ruta.c_str());
    string json, linea;
    if(!in.is_open()){
        throw runtime_error("No se pudo abrir: " + ruta);
    }
    while(getline(in, linea)){
        json += linea;
        json += '\n';
    }
    in.close();
    return json;
}

string trimSimple(const string& s){
    int i = 0;
    int j = (int)s.size() - 1;
    while(i <= j && s[i] == ' '){
        i++;
    }
    while(j >= i && s[j] == ' '){
        j--;
    }
    if(i > j){
        return "";
    }
    return s.substr(i, j - i + 1);
}

string extraerString(const string& texto, const string& key){
    string busc = "\"" + key + "\"";
    int p = texto.find(busc);
    if(p == (int)string::npos){
        return "";
    }
    p = texto.find(':', p);
    if(p == (int)string::npos){
        return "";
    }
    int a = texto.find('"', p);
    if(a == (int)string::npos){
        return "";
    }
    int b = a + 1;
    while(b < (int)texto.size()){
        if(texto[b] == '"' && texto[b-1] != '\\'){
            break;
        }
        b++;
    }
    if(b >= (int)texto.size()){
        return "";
    }
    return texto.substr(a + 1, b - a - 1);
}

string extraerNumeroComoString(const string& texto, const string& key){
    string busc = "\"" + key + "\"";
    int p = texto.find(busc);
    if(p == (int)string::npos){
        return "";
    }
    p = texto.find(':', p);
    if(p == (int)string::npos){
        return "";
    }
    p++;
    while(p < (int)texto.size() && texto[p] == ' '){
        p++;
    }
    int q = p;
    while(q < (int)texto.size() && texto[q] != ',' && texto[q] != '}'){
        q++;
    }
    return trimSimple(texto.substr(p, q - p));
}

string extraerObjeto(const string& texto, const string& key){
    string busc = "\"" + key + "\"";
    int p = texto.find(busc);
    if(p == (int)string::npos){
        return "";
    }
    p = texto.find(':', p);
    if(p == (int)string::npos){
        return "";
    }
    int a = texto.find('{', p);
    if(a == (int)string::npos){
        return "";
    }
    int bal = 0;
    for(int i = a; i < (int)texto.size(); i++){
        if(texto[i] == '{'){
            bal++;
        }else if(texto[i] == '}'){
            bal--;
        }
        if(bal == 0){
            return texto.substr(a, i - a + 1);
        }
    }
    return "";
}

string extraerCampoDeObjeto(const string& objeto, const string& key){
    return extraerString(objeto, key);
}

bool vSoloLetrasYAcentos(const string& s){
    regex r("^[A-Za-zÁÉÍÓÚÜÑáéíóúüñ ]+$");
    return regex_match(s, r);
}
bool vLetrasAcentosYpuntos(const string& s){
    regex r("^[A-Za-zÁÉÍÓÚÜÑáéíóúüñ .]+$");
    return regex_match(s, r);
}
bool vSoloDigitos(const string& s){
    regex r("^[0-9]+$");
    return regex_match(s, r);
}
bool vEmailBasico(const string& s){
    regex r("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");
    return regex_match(s, r);
}
bool vTelefonoSimple(const string& s){
    regex r("^[0-9]{3}-[0-9]{3}-[0-9]{4}$");
    return regex_match(s, r);
}

int main(){
    try{
        string json = leerArchivoComoString("entrada.json");

        int a = json.find('[');
        if(a == (int)string::npos){
            cout << "[!] No hay arreglo superior" << endl;
            return 0;
        }
        int bal = 0, b = -1;
        for(int i = a; i < (int)json.size(); i++){
            if(json[i] == '['){
                bal++;
            }else if(json[i] == ']'){
                bal--;
            }
            if(bal == 0){
                b = i;
                break;
            }
        }
        if(b == -1){
            cout << "[!] Arreglo sin cierre" << endl;
            return 0;
        }

        for(int i = a; i <= b; i++){
            if(json[i] == '{'){
                int balObj = 0, ini = i, fin = -1;
                for(int j = i; j <= b; j++){
                    if(json[j] == '{'){
                        balObj++;
                    }else if(json[j] == '}'){
                        balObj--;
                    }
                    if(balObj == 0){
                        fin = j;
                        i = j;
                        break;
                    }
                }
                if(fin == -1){
                    break;
                }
                string obj = json.substr(ini, fin - ini + 1);

                string idStr = extraerNumeroComoString(obj, "id");
                string nombreStr = extraerString(obj, "nombre");
                string edadStr = extraerNumeroComoString(obj, "edad");
                string ciudadStr = extraerString(obj, "ciudad");

                string detalles = extraerObjeto(obj, "detalles");
                string objContacto = extraerObjeto(detalles, "contacto");
                string objEmpleo = extraerObjeto(detalles, "empleo");

                string emailStr = extraerCampoDeObjeto(objContacto, "email");
                string telStr = extraerCampoDeObjeto(objContacto, "telefono");
                string puestoStr = extraerCampoDeObjeto(objEmpleo, "puesto");
                string empresaStr = extraerCampoDeObjeto(objEmpleo, "empresa");

                if(!vSoloDigitos(idStr)){
                    cout << "[X] id invalido: " << idStr << endl;
                }
                if(!vSoloLetrasYAcentos(nombreStr)){
                    cout << "[X] nombre invalido: " << nombreStr << endl;
                }
                if(!vSoloDigitos(edadStr)){
                    cout << "[X] edad invalida: " << edadStr << endl;
                }
                if(!vSoloLetrasYAcentos(ciudadStr)){
                    cout << "[X] ciudad invalida: " << ciudadStr << endl;
                }
                if(!vEmailBasico(emailStr)){
                    cout << "[X] email invalido: " << emailStr << endl;
                }
                if(!vTelefonoSimple(telStr)){
                    cout << "[X] telefono invalido: " << telStr << endl;
                }
                if(!vSoloLetrasYAcentos(puestoStr)){
                    cout << "[X] puesto invalido: " << puestoStr << endl;
                }
                if(!vLetrasAcentosYpuntos(empresaStr)){
                    cout << "[X] empresa invalida: " << empresaStr << endl;
                }

                cout << "ID: " << idStr << " | Nombre: " << nombreStr << " | Edad: " << edadStr << " | Ciudad: " << ciudadStr << " | Email: " << emailStr << " | Telefono: " << telStr << " | Puesto: " << puestoStr << " | Empresa: " << empresaStr << endl;
            }
        }
    }catch(const exception& e){
        cout << "Error: " << e.what() << endl;
    }
    return 0;
}
