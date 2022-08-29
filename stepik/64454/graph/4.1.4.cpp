#include "bits/stdc++.h"

using namespace std;

int main() {
    int N; cin >> N;

    vector<vector<int>> A(N, vector<int>(N, 0));
    for (int i = 0; i < N; ++i) {
        int sz; cin >> sz;
        for (int k = 0; k < sz; ++k) {
            int q; cin >> q;
            --q;
            A[i][q] = A[q][i] = 1;
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << A[i][j];
        }
        cout << '\n';
    }
}