#include <iostream>
#include <queue>
#include <vector>
#include <limits>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int k): key(k), left(NULL), right(NULL) {}
};

void printInorder(Node* r) {
    if (!r) return;
    printInorder(r->left);
    cout << r->key << " ";
    printInorder(r->right);
}
void printPreorder(Node* r) {
    if (!r) return;
    cout << r->key << " ";
    printPreorder(r->left);
    printPreorder(r->right);
}
void printPostorder(Node* r) {
    if (!r) return;
    printPostorder(r->left);
    printPostorder(r->right);
    cout << r->key << " ";
}
void printLevelOrder(Node* r) {
    if (!r) return;
    queue<Node*> q;
    q.push(r);
    while (!q.empty()) {
        Node* cur = q.front(); q.pop();
        cout << cur->key << " ";
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
}

Node* search(Node* r, int key, bool debug) {
    Node* cur = r;
    while (cur) {
        if (debug) cout << "[debug] busco " << key << " en " << cur->key << endl;
        if (key == cur->key) return cur;
        cur = (key < cur->key) ? cur->left : cur->right;
    }
    return NULL;
}

Node* insert(Node* r, int key, bool debug) {
    if (!r) {
        if (debug) cout << "[debug] inserto raiz " << key << endl;
        return new Node(key);
    }
    Node* cur = r;
    while (true) {
        if (debug) cout << "[debug] en " << cur->key << " comparo " << key << endl;
        if (key < cur->key) {
            if (!cur->left) { cur->left = new Node(key); if (debug) cout << "[debug] inserto izq " << key << endl; break; }
            cur = cur->left;
        } else if (key > cur->key) {
            if (!cur->right) { cur->right = new Node(key); if (debug) cout << "[debug] inserto der " << key << endl; break; }
            cur = cur->right;
        } else {
            if (debug) cout << "[debug] clave duplicada (ignorada): " << key << endl;
            break;
        }
    }
    return r;
}

Node* findMin(Node* r) {
    Node* cur = r;
    while (cur && cur->left) cur = cur->left;
    return cur;
}
Node* findMax(Node* r) {
    Node* cur = r;
    while (cur && cur->right) cur = cur->right;
    return cur;
}

Node* erase(Node* r, int key, bool debug) {
    if (!r) return NULL;
    if (key < r->key) {
        r->left = erase(r->left, key, debug);
    } else if (key > r->key) {
        r->right = erase(r->right, key, debug);
    } else {
        if (debug) cout << "[debug] elimino " << r->key << endl;
        if (!r->left && !r->right) {
            delete r; return NULL;
        }
        if (!r->left) {
            Node* t = r->right; delete r; return t;
        }
        if (!r->right) {
            Node* t = r->left; delete r; return t;
        }
        Node* succ = findMin(r->right);
        r->key = succ->key;
        r->right = erase(r->right, succ->key, debug);
    }
    return r;
}

int height(Node* r) {
    if (!r) return 0;
    int lh = height(r->left);
    int rh = height(r->right);
    return 1 + (lh > rh ? lh : rh);
}
int countTotal(Node* r) {
    if (!r) return 0;
    return 1 + countTotal(r->left) + countTotal(r->right);
}
int countLeaves(Node* r) {
    if (!r) return 0;
    if (!r->left && !r->right) return 1;
    return countLeaves(r->left) + countLeaves(r->right);
}
int countInternal(Node* r) {
    if (!r) return 0;
    if (!r->left && !r->right) return 0;
    return 1 + countInternal(r->left) + countInternal(r->right);
}

bool getMin(Node* r, int &out) {
    Node* m = findMin(r);
    if (!m) return false;
    out = m->key; return true;
}
bool getMax(Node* r, int &out) {
    Node* m = findMax(r);
    if (!m) return false;
    out = m->key; return true;
}

bool isBSTUtil(Node* r, long long lo, long long hi) {
    if (!r) return true;
    if (!(lo < r->key && r->key < hi)) return false;
    return isBSTUtil(r->left, lo, r->key) && isBSTUtil(r->right, r->key, hi);
}
bool isBST(Node* r) {
    return isBSTUtil(r, numeric_limits<long long>::min(), numeric_limits<long long>::max());
}

void inorderFill(Node* r, vector<int> &v) {
    if (!r) return;
    inorderFill(r->left, v);
    v.push_back(r->key);
    inorderFill(r->right, v);
}
Node* buildBalanced(const vector<int> &v, int l, int r) {
    if (l > r) return NULL;
    int m = (l + r) / 2;
    Node* root = new Node(v[m]);
    root->left = buildBalanced(v, l, m - 1);
    root->right = buildBalanced(v, m + 1, r);
    return root;
}
Node* balance(Node* r, bool debug) {
    vector<int> v;
    inorderFill(r, v);
    queue<Node*> q;
    if (r) q.push(r);
    while (!q.empty()) {
        Node* cur = q.front(); q.pop();
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
        delete cur;
    }
    if (debug) cout << "[debug] balanceo desde inorden (n=" << (int)v.size() << ")" << endl;
    return buildBalanced(v, 0, (int)v.size() - 1);
}

void freeTree(Node* r) {
    if (!r) return;
    freeTree(r->left);
    freeTree(r->right);
    delete r;
}

int main() {
    cout << "=== ABB BASICO ===" << endl;

    Node* root = NULL;
    bool debug = false;

    try {
        while (true) {
            cout << "\nMenu:\n";
            cout << "1) Insertar\n";
            cout << "2) Buscar\n";
            cout << "3) Eliminar\n";
            cout << "4) Recorridos\n";
            cout << "5) Altura y conteo\n";
            cout << "6) Min/Max\n";
            cout << "7) Validar ABB\n";
            cout << "8) Balancear\n";
            cout << "9) Toggle DEBUG (" << (debug ? "ON" : "OFF") << ")\n";
            cout << "0) Salir\n";
            cout << "Elige: ";

            int op;
            if (!(cin >> op)) { cin.clear(); string t; cin >> t; continue; }
            if (op == 0) break;

            if (op == 1) {
                cout << "Valor: "; int x; if (!(cin >> x)) { cin.clear(); string t; cin >> t; continue; }
                root = insert(root, x, debug);
                printInorder(root); cout << endl;
            } else if (op == 2) {
                cout << "Buscar: "; int x; if (!(cin >> x)) { cin.clear(); string t; cin >> t; continue; }
                Node* f = search(root, x, debug);
                cout << (f ? "Encontrado" : "No encontrado") << endl;
            } else if (op == 3) {
                cout << "Eliminar: "; int x; if (!(cin >> x)) { cin.clear(); string t; cin >> t; continue; }
                root = erase(root, x, debug);
                printInorder(root); cout << endl;
            } else if (op == 4) {
                cout << "Preorden: "; printPreorder(root); cout << endl;
                cout << "Inorden: "; printInorder(root); cout << endl;
                cout << "Postorden: "; printPostorder(root); cout << endl;
                cout << "Por niveles: "; printLevelOrder(root); cout << endl;
            } else if (op == 5) {
                cout << "Altura: " << height(root) << endl;
                cout << "Total: " << countTotal(root) << endl;
                cout << "Hojas: " << countLeaves(root) << endl;
                cout << "Internos: " << countInternal(root) << endl;
            } else if (op == 6) {
                int mn, mx;
                if (getMin(root, mn)) cout << "Min: " << mn << endl; else cout << "Min: vacio\n";
                if (getMax(root, mx)) cout << "Max: " << mx << endl; else cout << "Max: vacio\n";
            } else if (op == 7) {
                cout << (isBST(root) ? "Es ABB valido" : "No es ABB") << endl;
            } else if (op == 8) {
                root = balance(root, debug);
                printInorder(root); cout << endl;
            } else if (op == 9) {
                debug = !debug;
                cout << "DEBUG: " << (debug ? "ON" : "OFF") << endl;
            }
        }
    } catch (...) {
        cout << "Error inesperado." << endl;
    }

    freeTree(root);
    cout << "Fin." << endl;
    return 0;
}
