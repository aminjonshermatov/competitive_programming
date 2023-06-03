#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

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
  int n, m; cin >> n >> m;
  Dsu dsu(n);
  for (int i = 0; i < m; ++i) {
    int u, v; cin >> u >> v;
    --u, --v;
    dsu.merge(u, v);
  }
  for ()
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
