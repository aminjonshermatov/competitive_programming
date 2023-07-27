#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

constexpr auto inf = numeric_limits<i64>::max();

class Dsu {
  int n;
  vector<int> parent, rank;

  public:
  explicit Dsu(int n_) : n(n_) {
    parent.resize(n);
    iota(parent.begin(), parent.end(), 0);
    rank.assign(n, 1);
  }

  auto find(int v) -> int {
    assert(0 <= v && v < n);
    if (parent[v] != v) parent[v] = find(parent[v]);
    return parent[v];
  }

  auto merge(int v, int u) -> int {
    assert(0 <= v && v < n);
    assert(0 <= u && u < n);
    auto pv = find(v);
    auto pu = find(u);
    if (pv == pu) return pv;

    if (rank[pv] < rank[pu]) swap(pv, pu);
    parent[pu] = pv;
    if (rank[pv] == rank[pu]) ++rank[pv];
    return pv;
  }

  auto is_same(int v, int u) -> bool {
    assert(0 <= v && v < n);
    assert(0 <= u && u < n);
    return find(v) == find(u);
  }
};

void solve() {
  int n, m;
  cin >> n >> m;
  vector<int> hs(n);
  for (auto &h: hs) cin >> h;
  vector<vector<int>> g(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  int q;
  cin >> q;
  vector<tuple<int, int, int>> qs(q);
  vector<pair<int, int>> evs;
  for (int i = 0; auto &[u, v, e]: qs) {
    cin >> u >> v >> e;
    --u, --v;
    evs.emplace_back(hs[u] + e, ++i);
  }
  for (int i = 0; i < n; ++i) {
    evs.emplace_back(hs[i], -(i + 1));
  }

  vector<bool> seen(n, false);
  sort(evs.begin(), evs.end());

  Dsu dsu(n);
  vector<bool> ans(q);
  for (auto [e, id]: evs) {
    if (id > 0) {
      --id;
      ans[id] = dsu.is_same(get<0>(qs[id]), get<1>(qs[id]));
    } else {
      id *= -1;
      --id;
      for (auto u : g[id]) {
        if (seen[u]) {
          dsu.merge(id, u);
        }
      }
      seen[id] = true;
    }
  }

  for (auto x : ans) {
    cout << (x ? "Yes" : "No") << '\n';
  }
}

bool is_multi = true;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
  return 0;
}
