#include "bits/stdc++.h"

using namespace std;

template <typename T>
istream& operator>>(istream &in, vector<T> &arr) {
    for (auto &it : arr) in >> it;
    return in;
}

void solve() {
    int n, k;
    cin >> n >> k;

    if (k == 1) {
        cout << "YES" << '\n';
        for (int i = 1; i <= n; ++i) cout << i << '\n';
    } else {
        if (n & 1) cout << "NO" << '\n';
        else {
            cout << "YES" << '\n';
            vector<vector<int>> matrix(n, vector<int>(k));
            int cur = 0;
            for (int j = 0; j < k; ++j) {
                for (int i = 0; i < n; ++i) matrix[i][j] = ++cur;
            }

            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < k; ++j) cout << matrix[i][j] << ' ';
                cout << '\n';
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int tc = 1;
    cin >> tc;

    while (tc--) solve();
}