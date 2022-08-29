#include "bits/stdc++.h"

using namespace std;

int main() {
    int N, M; cin >> N >> M;

    vector<vector<int>> A(N, vector<int>(N, 0));
    for (int i = 0; i < M; ++i) {
        int p, q; cin >> p >> q;
        --p, --q;
        A[p][q] = A[q][p] = 1;
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << A[i][j];
        }
        cout << '\n';
    }
}