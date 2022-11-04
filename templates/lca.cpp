//
// Created by aminjon on 11/4/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll timer = 0, L;
vector<vector<ll>> G, up;
vector<ll> tin, tout;

void dfs(ll v, ll p) {
    tin[v] = ++timer;
    up[v][0] = p;
    for (ll i = 1; i <= L; ++i) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }

    for (auto u : G[v]) if (u != p) {
        dfs(u, v);
    }

    tout[v] = ++timer;
}

bool is_accessor(ll u, ll v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

ll lca(ll u, ll v) {
    if (is_accessor(u, v)) return u;
    if (is_accessor(v, u)) return v;

    for (ll i = L; i >= 0; --i) {
        if (!is_accessor(up[u][i], v)) u = up[u][i];
    }

    return up[u][0];
}

int main() {
    ll N, M;
    cin >> N >> M;

    G.resize(N + 1);
    tin.resize(N + 1);
    tout.resize(N + 1);
    timer = 0;
    L = ll(ceil(log2(N)));
    up.assign(N + 1, vector<ll>(L + 1));

    for (ll i = 0; i < M; ++i) {
        ll p, q;
        cin >> p >> q;
        G[p].push_back(q);
    }

    dfs(1, 1);

    for (ll p = 1; p <= N; ++p) {
        for (ll q = 1; q <= N; ++q) {
            cout << p << ' ' << q << '=' << lca(p, q) << '\n';
        }
    }
}