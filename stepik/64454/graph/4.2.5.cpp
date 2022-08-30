//
// Created by aminjon on 8/29/22.
//

#include "bits/stdc++.h"

using namespace std;

const int SZ = 501;
const int MAX_E = 124751;
vector<int> adj[SZ];
int8_t pr[MAX_E];
int edge[SZ][SZ];
vector<int> seen;
vector<int> D;
int N, M, Q, cur, k;

void dfs(int f) {
    seen[f] = cur;

    for (auto to : adj[f]) {
        if (seen[to] != cur && pr[edge[f][to]] == 1) {
            ++k;
            dfs(to);
        }
    }

    for (auto to : adj[f]) {
        if (seen[to] != cur) {
            k = -1e9;
            return;
        }
    }
}

auto main() -> int32_t {
    bool ok = false;
    memset(pr, 0, sizeof(int8_t) * MAX_E);
    memset(edge, 0, sizeof(int) * SZ * SZ);

    cin >> N >> M;
    seen.assign(N + 1, 0);

    for (int i = 0; i < M; ++i) {
        int p, q; cin >> p >> q;

        adj[p].emplace_back(q);
        adj[q].emplace_back(p);
        edge[p][q] = edge[q][p] = i + 1;
    }
    cin >> Q;
    D.resize(Q);
    for (auto &d : D) {
        cin >> d;
        pr[d] = 1;
    }

    for (int i = 1; i <= N && !ok; ++i) {
        cur = i;
        k = 0;
        dfs(i);
        ok = k == Q;
    }

    if (N == 1 && Q == 0) ok = true;
    if (Q != N - 1) ok = false;
    cout << (ok ? "YES" : "NO");
}