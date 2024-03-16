#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

struct DSU {
  int n, components;
  std::vector<int> parent, rank;

  explicit DSU(int n_) : n(n_), components(n), parent(n), rank(n, 1) {
    iota(parent.begin(), parent.end(), 0);
  }

  inline int find(int v) {
    assert(0 <= v && v < n);

    while (v != parent[v]) {
      v = parent[v] = parent[parent[v]];
    }
    return v;
  }

  bool merge(int u, int v) {
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    auto pu = find(u);
    auto pv = find(v);
    if (pu == pv) {
      return false;
    }

    if (rank[pu] < rank[pv]) {
      std::swap(pu, pv);
    }
    parent[pv] = pu;
    rank[pu] += rank[pv];
    --components;
    return true;
  }

  inline bool is_same(int u, int v) {
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    return find(u) == find(v);
  }
};

void solve() {
  int n, m, k;
  std::cin >> n >> m >> k;
  std::vector<std::tuple<int, int, int>> es(m);
  for (int i = 1; auto& [u, v, id] : es) {
    std::cin >> u >> v;
    --u, --v;
    id = i++;
  }
  DSU dsu(n);
  std::vector<int> ids, state(n, 0);
  for (auto [u, v, id] : es) {
    if (dsu.merge(u, v)) {
      ids.emplace_back(id);
      state[u] ^= 1;
      state[v] ^= 1;
    }
  }
  dbg(state);
  dbg(ids);
  auto x = std::accumulate(state.begin(), state.end(), 0);
  if (x % 2 != k % 2) {
    std::cout << "No\n";
    return;
  }
  std::set<int> to_del;
  for (; x < k && to_del.size() < ids.size();) {
    for (auto i : ids) {
      if (to_del.contains(i)) {
        continue;
      }
      auto [u, v, _] = es[i];
      if (state[u] + state[v] != 0) {
        continue;
      }
      to_del.emplace(i);
      state[u] ^= 1;
      state[v] ^= 1;
      x += 2;
    }
  }

  std::cout << "Yes\n";
  std::cout << ids.size() - to_del.size() << '\n';
  for (auto id : ids) {
    if (to_del.contains(id)) {
      continue;
    }
    std::cout << id << ' ';
  }
  std::cout << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}