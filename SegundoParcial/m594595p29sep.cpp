#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

pair<int, string> LCS(const string &X, const string &Y) {
    int m = (int)X.size();
    int n = (int)Y.size();

    vector<vector<int> > dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                if (dp[i - 1][j] >= dp[i][j - 1]) {
                    dp[i][j] = dp[i - 1][j];
                } else {
                    dp[i][j] = dp[i][j - 1];
                }
            }
        }
    }

    string lcs = "";
    int i = m;
    int j = n;

    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs += X[i - 1];
            i--;
            j--;
        } else {
            if (dp[i - 1][j] >= dp[i][j - 1]) {
                i--;
            } else {
                j--;
            }
        }
    }

    reverse(lcs.begin(), lcs.end());

    return make_pair(dp[m][n], lcs);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string X;
    string Y;

    while (true) {
        if (!getline(cin, X)) {
            break;
        }
        if (!getline(cin, Y)) {
            break;
        }

        pair<int, string> res = LCS(X, Y);
        cout << res.second << endl;
    }

    return 0;
}
