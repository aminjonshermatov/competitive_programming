//
// Created by aminjon on 11/8/22.
//
#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;

inline constexpr array<int, 5> dk{1, 0, -1, 0, 1};

auto solve() {
    int N, M;
    cin >> N >> M;

    auto is_safe = [&](int i, int j) { return i >= 0 && i < N && j >= 0 && j < M; };

    pii S, E;
    cin >> S.first >> S.second >> E.first >> E.second;

    vector<string> adj(N);
    for (auto &r : adj) cin >> r;

    /*if (!is_safe(S.first, S.second) || adj[S.first][S.second] != '0'
     || !is_safe(E.first, E.second) || adj[E.first][E.second] != '0') { cout << "NO"; return; }*/

    queue<pii> q;
    adj[S.first][S.second] = '?';
    q.emplace(S);
    while (!q.empty()) {
        auto [i, j] = q.front(); q.pop();

        if (i == E.first && j == E.second) { cout << "YES"; return; }

        for (int k = 0; k < 4; ++k) {
            int ii = i + dk[k], jj = j + dk[k + 1];
            if (is_safe(ii, jj) && adj[ii][jj] == '0') {
                adj[ii][jj] = '?';
                q.emplace(ii, jj);
            }
        }
    }

    cout << "NO";
}

int main() {
    solve();
}