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

using i64 = int64_t;

void solve() {
  int n;
  cin >> n;
  struct Point {
    int x, y, id;
  };
  vector<Point> ps(n);
  for (int i = 0; auto &[x, y, id]: ps) {
    cin >> x >> y;
    id = i++;
  }
  struct Edge {
    int u, v;
    i64 d;
    bool operator<(const Edge &other) const {
      return d < other.d;
    }
  };
  vector<Edge> es;
  es.reserve(2 * n);
  sort(ps.begin(), ps.end(), [](const Point &lhs, const Point &rhs) {
    return lhs.x < rhs.x;
  });
  for (int i = 1; i < ps.size(); ++i) {
    es.emplace_back(Edge{ps[i - 1].id, ps[i].id, ps[i].x - ps[i - 1].x});
  }
  sort(ps.begin(), ps.end(), [](const Point &lhs, const Point &rhs) {
    return lhs.y < rhs.y;
  });
  for (int i = 1; i < ps.size(); ++i) {
    es.emplace_back(Edge{ps[i - 1].id, ps[i].id, ps[i].y - ps[i - 1].y});
  }

  sort(es.begin(), es.end());
  Dsu dsu(n);
  i64 ans = 0;
  for (auto &[u, v, d] : es) {
    if (dsu.find(u) != dsu.find(v)) {
      ans += d;
      dsu.merge(u, v);
    }
  }
  cout << ans << '\n';
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
