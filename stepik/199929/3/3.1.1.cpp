//
// Created by aminjon on 11/8/22.
//
#include <bits/stdc++.h>

using namespace std;

auto solve() {
    int N;
    cin >> N;
    vector<vector<int>> adj(N, vector<int>(N, 0));
    for (int i = 0; i < N; ++i) {
        int k;
        cin >> k;
        for (int _ = 0; _ < k; ++_) {
            int j;
            cin >> j;
            adj[i][j - 1] = 1;
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << adj[i][j] << ' ';
        }
        cout << '\n';
    }
}

int main() {
    solve();
}