#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

struct NodoDist {
    string nodo;
    int dist;
    bool operator>(const NodoDist &otro) const {
        return dist > otro.dist;
    }
};

int main() {
    unordered_map<string, vector<pair<string, int>>> grafo;

    grafo["s"].push_back(make_pair("b", 4));
    grafo["b"].push_back(make_pair("s", 4));

    grafo["s"].push_back(make_pair("c", 2));
    grafo["c"].push_back(make_pair("s", 2));

    grafo["b"].push_back(make_pair("d", 5));
    grafo["d"].push_back(make_pair("b", 5));

    grafo["c"].push_back(make_pair("d", 8));
    grafo["d"].push_back(make_pair("c", 8));

    grafo["c"].push_back(make_pair("e", 10));
    grafo["e"].push_back(make_pair("c", 10));

    grafo["e"].push_back(make_pair("d", 2));
    grafo["d"].push_back(make_pair("e", 2));

    grafo["d"].push_back(make_pair("t", 6));
    grafo["t"].push_back(make_pair("d", 6));

    grafo["e"].push_back(make_pair("t", 2));
    grafo["t"].push_back(make_pair("e", 2));

    cout << "Grafo cargado. Nodos: s, b, c, d, e, t" << endl;
    cout << "Ingresa el origen: ";
    string origen;
    cin >> origen;
    cout << "Ingresa el destino: ";
    string destino;
    cin >> destino;

    if (grafo.find(origen) == grafo.end() || grafo.find(destino) == grafo.end()) {
        cout << "Error: origen o destino no existen en el grafo." << endl;
        return 0;
    }

    unordered_map<string, int> dist;
    unordered_map<string, string> padre;
    const int INF = numeric_limits<int>::max();

    for (auto &par : grafo) {
        dist[par.first] = INF;
        padre[par.first] = "";
    }

    dist[origen] = 0;

    priority_queue<NodoDist, vector<NodoDist>, greater<NodoDist>> pq;
    pq.push(NodoDist{origen, 0});

    while (!pq.empty()) {
        NodoDist actual = pq.top();
        pq.pop();

        if (actual.dist > dist[actual.nodo]) {
            continue;
        }

        vector<pair<string, int>> &vecinos = grafo[actual.nodo];
        for (size_t i = 0; i < vecinos.size(); i++) {
            string v = vecinos[i].first;
            int w = vecinos[i].second;

            if (dist[actual.nodo] != INF) {
                int nueva = dist[actual.nodo] + w;
                if (nueva < dist[v]) {
                    dist[v] = nueva;
                    padre[v] = actual.nodo;
                    pq.push(NodoDist{v, nueva});
                }
            }
        }
    }

    if (dist[destino] == INF) {
        cout << "No existe camino desde " << origen << " hasta " << destino << "." << endl;
        return 0;
    }

    // Reconstruir el camino
    vector<string> camino;
    string actual = destino;
    while (actual != "") {
        camino.push_back(actual);
        if (actual == origen) {
            break;
        }
        actual = padre[actual];
    }
    reverse(camino.begin(), camino.end());

    cout << "Distancia minima desde " << origen << " hasta " << destino << ": " << dist[destino] << endl;
    cout << "Camino: ";
    for (size_t i = 0; i < camino.size(); i++) {
        cout << camino[i];
        if (i + 1 < camino.size()) {
            cout << " -> ";
        }
    }
    cout << endl;

    return 0;
}
