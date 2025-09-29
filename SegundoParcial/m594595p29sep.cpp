#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

int valor(char c) {
    return c - 'A';
}

int minDistBetweenConsecutives(const string &t) {
    int n = static_cast<int>(t.size());
    if (n <= 1) {
        return 0;
    }
    int mn = 1000000;
    for (int i = 0; i < n - 1; i++) {
        int d = abs(valor(t[i + 1]) - valor(t[i]));
        if (d < mn) {
            mn = d;
        }
    }
    return mn;
}

int main() {
    try {
        string s;
        while (cin >> s) {
            int L = static_cast<int>(s.size());
            vector<string> seq(21);
            seq[10] = s;
            string tmp = s;
            for (int i = 9; i >= 0; i--) {
                prev_permutation(tmp.begin(), tmp.end());
                seq[i] = tmp;
            }
            tmp = s;
            for (int i = 11; i < 21; i++) {
                next_permutation(tmp.begin(), tmp.end());
                seq[i] = tmp;
            }

            int bestMin = -1;
            string bestPerm = "";
            for (int i = 0; i < 21; i++) {
                int mnd = minDistBetweenConsecutives(seq[i]);
                if (mnd > bestMin) {
                    bestMin = mnd;
                    bestPerm = seq[i];
                } else if (mnd == bestMin) {
                    if (seq[i] < bestPerm) {
                        bestPerm = seq[i];
                    }
                }
            }

            cout << bestPerm << bestMin << endl;
        }
    }
    catch(...) {
        cout << "Error" << endl;
    }
    return 0;
}
