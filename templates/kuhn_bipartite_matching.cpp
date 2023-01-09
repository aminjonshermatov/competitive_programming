//
// Created by aminjon on 1/9/23.
//
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

#define eb      emplace_back
#define all(x)  (x).begin(), (x).end()
#define sz(x)   (ll)((x).size())

#define rep(i, b)       for (auto i = 0; (i) < (b); ++(i))
#define forr(el, cont)  for (auto &(el) : (cont))

struct kuhn_bipartite_matching {
    vector<vector<int>> &g;
    int n, m;

    kuhn_bipartite_matching(int n_, int m_, vector<vector<int>> &g_) : n(n_), m(m_), g(g_) { }

    vector<pii> get_pairs() {
        vector<int> mt(m, -1);
        vector<bool> used(n);

        auto try_kuhn = [&](auto f, int v) -> bool {
            if (used[v]) return false;
            used[v] = true;
            forr(u, g[v]) if (mt[u] == -1 || f(f, mt[u])) {
                    mt[u] = v;
                    return true;
                }

            return false;
        };

        rep(v, n) {
            fill(all(used), false);
            try_kuhn(try_kuhn, v);
        }

        vector<pii> pairs;
        rep(u, m) if (mt[u] != -1) pairs.eb(mt[u] + 1, u + 1);
        return pairs;
    }
};

void solve() {
    int n, m, k; cin >> n >> m >> k;

    vector<vector<int>> g(n);
    rep(_, k) {
        int a, b; cin >> a >> b;
        --a, --b;

        g[a].eb(b);
    }

    kuhn_bipartite_matching kbm(n, m, g);
    auto pairs = kbm.get_pairs();

    cout << sz(pairs) << '\n';
    for (auto [v, u] : pairs) cout << v << ' ' << u << '\n';
}