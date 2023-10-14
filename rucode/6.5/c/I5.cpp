#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

struct MinCostMaxFlow {
    using i64 = int64_t;
    static constexpr auto inf = numeric_limits<i64>::max();

    struct FlowEdge {
      int u, v;
      i64 cap, flow, cost;
      int id;
      FlowEdge(int u_, int v_, i64 cap_, i64 cost_, int id_) : u(u_), v(v_), cap(cap_), flow(0), cost(cost_), id(id_) { }
    };

    int n;
    vector<vector<int>> g;
    vector<FlowEdge> edges;
    vector<i64> pot, dist;
    vector<int> pre;
    explicit MinCostMaxFlow(int n_) : n(n_) {
      g.resize(n);
      pot.resize(n);
      dist.resize(n);
      pre.resize(n);
    }
    void add_edge(int u, int v, i64 cap, i64 cost, int id) {
      g[u].emplace_back(edges.size());
      edges.emplace_back(u, v, cap, cost, id);
      g[v].emplace_back(edges.size());
      edges.emplace_back(v, u, 0, -cost, -1);
    }

    bool dijkstra(int S, int T) {
      dist.assign(n, inf);
      pre.assign(n, -1);

      using U = pair<i64, int>;
      priority_queue<U, vector<U>, greater<>> pq;
      pq.emplace(dist[S] = 0, S);
      while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        for (auto id : g[u]) {
          auto v = edges[id].v;
          if (edges[id].cap - edges[id].flow <= 0) continue;
          auto nd = d + edges[id].cost + pot[u] - pot[v];
          if (nd < dist[v]) {
            dist[v] = nd;
            pre[v] = id;
            pq.emplace(dist[v] = nd, v);
          }
        }
      }
      return dist[T] != inf;
    }

    decltype(auto) flow(int S, int T) {
      fill(pot.begin(), pot.end(), 0);
      bool any;
      for (int _ = 0; _ < n && any; ++_) {
        any = false;
        for (const auto &edge : edges) {
          if (edge.cap == 0) continue;
          auto npot = pot[edge.u] + edge.cost;
          if (pot[edge.v] > npot) {
            any |= true;
            pot[edge.v] = npot;
          }
        }
      }
      assert(!any); // cycle of negative weight

      i64 flow = 0, cost = 0;
      while (dijkstra(S, T)) {
        for (int v = 0; v < n; ++v) {
          pot[v] += dist[v];
        }
        auto nf = inf;
        for (int v = T; v != S; v = edges[pre[v]].u) {
          nf = min(nf, edges[pre[v]].cap - edges[pre[v]].flow);
        }
        flow += nf;
        cost += (pot[T] - pot[S]) * nf;
        for (int v = T; v != S; v = edges[pre[v]].u) {
          edges[pre[v]].flow += nf;
          edges[pre[v] ^ 1].flow -= nf;
        }
      }
      /*const auto mx_id = max_element(edges.begin(), edges.end(), [](const FlowEdge &lhs, const FlowEdge &rhs) {
        return lhs.id < rhs.id;
      })->id;
      vector<i64> fall_through(mx_id + 1, 0);*/
      map<int, i64> fall_through;
      for (const auto &edge : edges) {
        if (edge.id != -1 && edge.flow > 0) {
          fall_through[edge.id] = edge.flow;
        }
      }
      return tuple{flow, cost, fall_through};
    }
};

void solve() {
  int n;
  cin >> n;

  MinCostMaxFlow mcmf(n * 2 + 2);
  for (int i = 1; i <= n; ++i) {
    mcmf.add_edge(0, i, 1, 0, -1);
    mcmf.add_edge(n + i, 2 * n + 1, 1, 0, -1);
    for (int j = 1; j <= n; ++j) {
      int c;
      cin >> c;
      mcmf.add_edge(i, n + j, 1, c, i * n + j);
    }
  }
  auto [f, c, fall_th] = mcmf.flow(0, 2 * n + 1);
  dbg(f, c, fall_th);
  vector<int> cols(n, -1);
  for (auto [id, fl] : fall_th) {
    auto [ii, jj] = div(id - 1, n);
    assert(clamp(ii, 1, n) == ii && clamp(jj, 0, n - 1) == jj);
    cols[ii - 1] = jj;
  }
  assert(all_of(cols.begin(), cols.end(), [](auto j) { return j >= 0; }));
  assert(set(cols.begin(), cols.end()).size() == n);
  cout << c << '\n';
  for (int i = 0; i < n; ++i) {
    cout << cols[i] + 1 << ' ';
  }
  cout << '\n';
}

bool is_multi = false;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
  return 0;
}
