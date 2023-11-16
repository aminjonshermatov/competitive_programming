#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

template <typename Node> struct DsuWeighted {
  int n, components;
  std::vector<int> parent, rank;
  std::vector<Node> weight;

  explicit DsuWeighted(int n_) : n(n_), components(n), parent(n), rank(n, 1), weight(n, Node()) {
    iota(parent.begin(), parent.end(), 0);
  }

  inline decltype(auto) find(int v) {
    assert(0 <= v && v < n);
    auto res = Node();

    while (v != parent[v]) {
      res = Node::unite(res, weight[v]);
      res = Node::unite(res, weight[parent[v]]);
      weight[v] = Node::unite(weight[v], weight[parent[v]]);
      v = parent[v] = parent[parent[v]];
    }
    return std::pair(v, res);
  }

  bool merge(int u, int v, Node w) {
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    auto [pu, wu] = find(u);
    auto [pv, wv] = find(v);
    if (pu == pv) {
      return false;
    }

    if (rank[pu] < rank[pv]) {
      std::swap(pv, pu);
      std::swap(wv, wu);
      w = Node::inverse(w);
    }
    // U - V = w
    // weight[v] - weight[u] + ? = w
    // ? = weight[u] - weight[v] + w
    parent[pv] = pu;
    rank[pu] += rank[pv];
    weight[pv] = Node::unite(wu, Node::unite(Node::inverse(wv), w));
    --components;
    return true;
  }

  inline bool is_same(int u, int v) {
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    return find(u).first == find(v).first;
  }
};

using i64 = int64_t;
struct Node {
  i64 val = 0;
  inline static Node unite(Node a, Node b) {
    return Node{a.val + b.val};
  }
  inline static Node inverse(Node a) {
    return Node{-a.val};
  }
  inline bool operator==(const Node &node) const noexcept {
    return val == node.val;
  }
};

void solve() {
  int n, q;
  std::cin >> n >> q;

  DsuWeighted<Node> dsuw(n);
  std::vector<int> s;
  for (int i = 1; i <= q; ++i) {
    int u, v;
    i64 w;
    std::cin >> u >> v >> w;
    --u, --v;
    auto [pu, wu] = dsuw.find(u);
    auto [pv, wv] = dsuw.find(v);

    if (pu != pv) {
      s.emplace_back(i);
      dsuw.merge(u, v, {w});
      continue;
    }
    if (wv != Node::unite(wu, {w})) continue;
    s.emplace_back(i);
  }
  for (auto i : s) {
    std::cout << i << ' ';
  }
  std::cout << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}