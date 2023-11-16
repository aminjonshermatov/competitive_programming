#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

struct DsuRollback {
  int n, components;
  std::vector<int> parent, rank;

  enum class UpdateType : uint8_t { kUpdateRank, kUpdateParent };
  // <update_type, vertex, old_val>
  std::vector<std::tuple<UpdateType, int, int>> history;

  explicit DsuRollback(int n_) : n(n_), components(n), parent(n), rank(n, 1) {
    iota(parent.begin(), parent.end(), 0);
  }

  inline int find(int v) {
    assert(0 <= v && v < n);
    if (parent[v] != v) {
      history.emplace_back(UpdateType::kUpdateParent, v, parent[v]);
      parent[v] = find(parent[v]);
    }
    return parent[v];
  }

  bool merge(int u, int v) {
    assert(0 <= v && v < n);
    assert(0 <= u && u < n);
    auto pv = find(v);
    auto pu = find(u);
    if (pv == pu) {
      return false;
    }

    if (rank[pv] < rank[pu]) {
      std::swap(pv, pu);
    }
    history.emplace_back(UpdateType::kUpdateParent, pu, parent[pu]);
    parent[pu] = pv;
    history.emplace_back(UpdateType::kUpdateRank, pv, rank[pv]);
    rank[pv] += rank[pu];
    --components;
    return true;
  }

  inline bool is_same(int u, int v) {
    assert(0 <= v && v < n);
    assert(0 <= u && u < n);
    return find(v) == find(u);
  }

  void rollback() {
    while (std::get<0>(history.back()) != UpdateType::kUpdateRank) {
      auto [_, v, old_parent] = history.back();
      parent[v] = old_parent;
      history.pop_back();
    }
    assert(!history.empty());
    {
      auto [type, v, old_rank] = history.back();
      assert(type == UpdateType::kUpdateRank);
      history.pop_back();
      rank[v] = old_rank;
    }
    {
      auto [type, v, old_parent] = history.back();
      assert(type == UpdateType::kUpdateParent);
      history.pop_back();
      parent[v] = old_parent;
    }
    ++components;
  }
};

using i64 = int64_t;
constexpr auto inf = std::numeric_limits<i64>::max();

struct Edge {
  int u, v;
  i64 w;
};

void solve() {
  int n, m;
  i64 k;
  std::cin >> n >> m >> k;
  std::vector<Edge> es(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> es[i].u >> es[i].v >> es[i].w;
    --es[i].u, --es[i].v;
  }

  DsuRollback dsur(n);
  i64 ans = inf;
  auto rec = [&](auto &f, int id, i64 cost) -> void {
    if (dsur.components == 1) {
      ans = std::min(ans, cost % k);
      return;
    }
    if (id >= m) return;

    f(f, id + 1, cost);
    if (!dsur.is_same(es[id].u, es[id].v)) {
      dsur.merge(es[id].u, es[id].v);
      f(f, id + 1, cost + es[id].w);
      dsur.rollback();
    }
  };
  rec(rec, 0, 0);
  std::cout << ans << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}