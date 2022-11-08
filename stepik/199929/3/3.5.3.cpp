//
// Created by aminjon on 11/8/22.
//
#include <bits/stdc++.h>

using namespace std;

auto solve() {
    int N;
    cin >> N;

    vector<vector<int>> dist(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> dist[i][j];
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    int mx = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            mx = max(mx, dist[i][j]);
        }
    }
    cout << mx;
}

int main() {
    solve();
}