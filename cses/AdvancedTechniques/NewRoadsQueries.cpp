#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

struct Dsu {
  int n, components;
  std::vector<int> parent, rank;

  explicit Dsu(int n_) : n(n_), components(n), parent(n), rank(n, 1) {
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

template <typename T, template <typename> typename DataStructure> struct HeavyLightDecomposition {
  std::vector<int> parent, root, depth, treePos, heavy;
  DataStructure<T> ds;

  HeavyLightDecomposition() = default;
  template <typename G> explicit HeavyLightDecomposition(G&& g) {
    init(std::forward<G>(g));
  }

  template <typename G> void init(G&& g) {
    const auto n = int(g.size());
    parent.assign(n, -1);
    root.assign(n, -1);
    treePos.assign(n, -1);
    heavy.assign(n, -1);
    depth.resize(n);
    depth[0] = 0;

    auto dfs = [&](auto& f, int v) -> int {
      int size = 1, maxSubtree = 0;
      for (auto u : g[v]) {
        if (u == parent[v]) continue;
        parent[u] = v;
        depth[u] = depth[v] + 1;
        auto subtree = f(f, u);
        if (subtree > maxSubtree) {
          heavy[v] = u;
          maxSubtree = subtree;
        }
        size += subtree;
      }
      return size;
    };
    dfs(dfs, 0);

    for (int u = 0, currentPos = 0; u < n; ++u) {
      if (parent[u] == -1 || heavy[parent[u]] != u) {
        for (int v = u; v != -1; v = heavy[v]) {
          root[v] = u;
          treePos[v] = currentPos++;
        }
      }
    }
    ds.init(n);
  }

  template <typename F> void processPath(int u, int v, F&& op) {
    for (; root[u] != root[v]; v = parent[root[v]]) {
      if (depth[root[u]] > depth[root[v]]) {
        std::swap(u, v); // u closer to lca rather than v
      }
      op(treePos[root[v]], treePos[v] + 1);
    }
    if (depth[u] > depth[v]) {
      std::swap(u, v);
    }
    op(treePos[u] + 1, treePos[v] + 1);
  }

  void modify(int v, const T& val) {
    ds.modify(treePos[v], val);
  }

  T query(int u, int v) { // [u, v]
    auto res = T();
    processPath(u, v, [this, &res](int l, int r) { // [l, r)
      res = T::unite(res, ds.query(l, r));
    });
    return res;
  }
};

template <typename Node> struct BottomUpSegmentTree {
  int n = 0;
  std::vector<Node> nodes;

  BottomUpSegmentTree() = default;
  explicit BottomUpSegmentTree(int n_) { init(std::vector(n_, Node())); }
  BottomUpSegmentTree(int n_, Node node) { init(std::vector(n_, node)); }
  template <typename T> explicit BottomUpSegmentTree(std::vector<T> init_) { init(init_); }

  void init(int n_) { init(std::vector(n_, Node())); }
  template <typename T> void init(std::vector<T> init_) {
    n = init_.size();
    nodes.assign(2 * init_.size(), Node());
    for (int i = 0; i < init_.size(); ++i) {
      modify(i, Node{init_[i]});
    }
  }

  void modify(int pos, Node val) {
    for (nodes[pos += n] = val; pos > 1;) {
      pos >>= 1;
      nodes[pos] = Node::unite(nodes[pos << 1], nodes[pos << 1 | 1]);
    }
  }
  Node query(int l, int r) {
    auto ans = Node();
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) ans = Node::unite(ans, nodes[l++]);
      if (r & 1) ans = Node::unite(ans, nodes[--r]);
    }
    return ans;
  }
};

struct Node {
  int val = 0;
  static Node unite(Node a, Node b) {
    return Node{std::max(a.val, b.val)};
  }
};

struct Edge {
  int u, v, w;
};
struct Query {
  int u, v, id;
};

void solve() {
  int n, m, q;
  std::cin >> n >> m >> q;
  std::vector<Edge> es(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> es[i].u >> es[i].v;
    --es[i].u, --es[i].v;
    es[i].w = i + 1;
  }

  std::ranges::sort(es, [](const Edge& a, const Edge& b) {
    return a.w < b.w;
  });

  Dsu dsu(n);
  std::vector<int> used_edges;
  for (int i = 0; i < m; ++i) {
    if (dsu.merge(es[i].u, es[i].v)) {
      used_edges.emplace_back(i);
    }
  }

  std::vector<int> comp(n);
  std::map<int, int> ids;
  for (int v = 0; v < n; ++v) {
    ids[dsu.find(v)];
  }
  int id = 0;
  for (auto& [a, b] : ids) {
    b = id++;
  }
  std::vector<std::vector<int>> comp_nodes(id);
  for (int v = 0; v < n; ++v) {
    comp_nodes[comp[v] = ids[dsu.find(v)]].emplace_back(v);
  }
  for (int i = 0; i < id; ++i) {
    std::ranges::sort(comp_nodes[i]);
  }
  std::vector<std::vector<int>> comp_edges(id);
  for (auto e_id : used_edges) {
    comp_edges[comp[es[e_id].u]].emplace_back(e_id);
  }
  std::vector<std::vector<Query>> qs(id);
  for (int i = 0; i < q; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    qs[comp[dsu.find(u)]].emplace_back(u, v, i);
  }
  using HLD = HeavyLightDecomposition<Node, BottomUpSegmentTree>;
  std::vector<int> ans(q, -1);
  for (int cid = 0; cid < id; ++cid) {
    std::vector<std::vector<int>> g(comp_nodes[cid].size());

    for (auto e_id : comp_edges[cid]) {
      auto u = int(std::ranges::lower_bound(comp_nodes[cid], es[e_id].u) - comp_nodes[cid].begin());
      auto v = int(std::ranges::lower_bound(comp_nodes[cid], es[e_id].v) - comp_nodes[cid].begin());
      g[u].emplace_back(v);
      g[v].emplace_back(u);
    }
    HLD hld(g);
    for (auto e_id : comp_edges[cid]) {
      auto u = int(std::ranges::lower_bound(comp_nodes[cid], es[e_id].u) - comp_nodes[cid].begin());
      auto v = int(std::ranges::lower_bound(comp_nodes[cid], es[e_id].v) - comp_nodes[cid].begin());
      hld.modify(hld.parent[u] == v ? u : v, {es[e_id].w});
    }
    for (auto [u, v, q_id] : qs[cid]) {
      if (comp[u] != comp[v]) continue;
      auto uu = int(std::ranges::lower_bound(comp_nodes[cid], u) - comp_nodes[cid].begin());
      auto vv = int(std::ranges::lower_bound(comp_nodes[cid], v) - comp_nodes[cid].begin());
      ans[q_id] = hld.query(uu, vv).val;
    }
  }
  for (int i = 0; i < q; ++i) {
    std::cout << ans[i] << '\n';
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}