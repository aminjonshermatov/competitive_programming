#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define all(x) begin(x), end(x)
#define rep(i, n) for (int (i) = 0; i < (n); ++i)

inline constexpr auto inf = numeric_limits<ll>::max();

struct max_flow {
    vector<vector<ll>> &adj;
    vector<int> pa;
    vector<bool> used;
    int n;

    max_flow(int n_, vector<vector<ll>> &adj_)
            : n(n_) , adj(adj_){ }

    bool bfs(int s, int t) {
        fill(all(used), false);
        used[s] = true;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            auto v = q.front(); q.pop();
            rep(u, n) if (!used[u] && adj[v][u] > 0) {
                pa[u] = v;
                used[u] = true;
                q.push(u);
            }
        }
        return used[t];
    }

    ll flow(int s, int t) {
        ll flow = 0;
        pa.resize(n);
        used.resize(n);

        while (bfs(s, t)) {
            ll cur_f = inf;
            for (int v = t; v != s; v = pa[v]) {
                int u = pa[v];
                cur_f = min(cur_f, adj[u][v]);
            }
            flow += cur_f;
            for (int v = t; v != s; v = pa[v]) {
                int u = pa[v];
                adj[u][v] -= cur_f;
                adj[v][u] += cur_f;
            }
        }

        return flow;
    }
};