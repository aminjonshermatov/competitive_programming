//
// Created by aminjon on 8/29/22.
//

#include "bits/stdc++.h"

using namespace std;


auto main() -> int32_t {
    int N, M;
    cin >> N >> M;

    unordered_map<int, set<int>> adj;
    vector<int> L(N, -1);

    for (int i = 0; i < M; ++i) {
        int p, q; cin >> p >> q;
        --p, --q;

        adj[p].insert(q);
        adj[q].insert(p);
    }

    int idx = 0;
    queue<int> q;
    for (int i = 0; i < N; ++i) {
        if (L[i] == -1) {
            L[i] = ++idx;
            q.push(i);

            while (!q.empty()) {
                auto it = q.front(); q.pop();

                for (auto o : adj[it]) {
                    if (L[o] == -1) {
                        L[o] = idx;
                        q.push(o);
                    }
                }
            }
        }
    }

    cout << idx << '\n';
    for (int i = 0; i < N; ++i) cout << L[i] << ' ';
    cout << '\n';
}