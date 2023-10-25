//
// Created by aminjon on 3/12/23.
//
#include <bits/stdc++.h>

template <typename T> struct FenwickTreeRangeUpdateRangeQuery {
  int n = 0;
  std::vector<T> bitA, bitB;

  FenwickTreeRangeUpdateRangeQuery() = default;
  explicit FenwickTreeRangeUpdateRangeQuery(int n_) : n(n_), bitA(n_, T(0)), bitB(n_, T(0))  { }
  template<typename U> explicit FenwickTreeRangeUpdateRangeQuery(const std::vector<U> &A) : n(A.size()) , bitA(A.size(), T(0)), bitB(A.size(), T(0)) {
    for (auto idx = 0u; idx < n; ++idx) {
      modify(idx, idx + 1, A[idx]);
    }
  }

  void init(int n_) {
    n = n_;
    bitA.assign(n, T(0));
    bitB.assign(n, T(0));
  }

  auto modify(std::vector<T> &bit, int idx, T val) -> void {
    for (; idx < n; idx = idx | (idx + 1)) {
      bit[idx] += val;
    }
  }

  auto modify(int l, int r, T val) -> void { // [, r)
    modify(bitA, l, val);
    modify(bitA, r, -val);
    modify(bitB, l, val * (l - 1));
    modify(bitB, r, -val * (r - 1));
  }

  [[nodiscard]] auto query(const std::vector<T> &bit, int idx) const -> T {
    T ret = T(0);
    for (; idx >= 0; idx = (idx & (idx + 1)) - 1) {
      ret += bit[idx];
    }
    return ret;
  }

  [[nodiscard]] auto prefix_query(int idx) const -> T {
    return query(bitA, idx) * idx - query(bitB, idx);
  }

  [[nodiscard]] auto query(int l, int r) const -> T {
    return prefix_query(r - 1) - prefix_query(l - 1);
  }
  [[nodiscard]] auto query(int idx) const -> T {
    return prefix_query(idx) - prefix_query(idx - 1);
  }
};

template<typename T, template<typename> typename DataStructure> struct HeavyLightDecomposition {
  std::vector<int> parent, root, depth, treePos, heavy;
  DataStructure<T> tree;

  template<typename G> explicit HeavyLightDecomposition(const G &g) {
    const auto n = int(g.size());
    parent.assign(n, -1);
    root.assign(n, -1);
    treePos.assign(n, -1);
    heavy.assign(n, -1);
    depth.resize(n);
    depth[0] = 0;
    dfs(g, 0);

    for (int u = 0, currentPos = 0; u < n; ++u) {
      if (parent[u] == -1 || heavy[parent[u]] != u) {
        for (int v = u; v != -1; v = heavy[v]) {
          root[v] = u;
          treePos[v] = currentPos++;
        }
      }
    }
    tree.init(n);
  }

  template<typename G> int dfs(const G &g, int v) {
    int size = 1, maxSubtree = 0;
    for (auto u : g[v]) {
      if (u == parent[v]) continue;
      parent[u] = v;
      depth[u] = depth[v] + 1;
      auto subtree = dfs(g, u);
      if (subtree > maxSubtree) {
        heavy[v] = u;
        maxSubtree = subtree;
      }
      size += subtree;
    }
    return size;
  }

  template<typename BinaryOP> void processPath(int u, int v, BinaryOP op) {
    for (; root[u] != root[v]; v = parent[root[v]]) {
      if (depth[root[u]] > depth[root[v]]) {
        std::swap(u, v); // u closer to lca rather than v
      }
      op(treePos[root[v]], treePos[v] + 1);
    }
    if (depth[u] > depth[v]) {
      std::swap(u, v);
    }
    op(treePos[u], treePos[v] + 1);
  }

  void modify(int v, const T &val) {
    modify(v, v, val);
  }
  void modify(int u, int v, const T &val) { // [u, v]
    processPath(u, v, [this, &val](int l, int r) { // [l, r)
      tree.modify(l, r, val);
    });
  }

  T query(int u, int v) { // [u, v]
    T res(0);
    processPath(u, v, [this, &res](int l, int r) { // [l, r)
      res += tree.query(l, r);
    });
    return res;
  }
};