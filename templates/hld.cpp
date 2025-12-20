//
// Created by aminjon on 3/12/23.
//
#include <bits/stdc++.h>

class HeavyLightDecomposition final {
 public:
  template<typename G>
  explicit HeavyLightDecomposition(const G &g) : N_(static_cast<int>(g.size())) {
    Parent_.assign(N_, -1);
    Root_.assign(N_, -1);
    TreePos_.assign(N_, -1);
    Heavy_.assign(N_, -1);
    Depth_.resize(N_);
    Depth_[0] = 0;
    Dfs(g, 0);

    for (auto u = 0, currentPos = 0; u < N_; ++u) {
      if (Parent_[u] == -1 || Heavy_[Parent_[u]] != u) {
        for (auto v = u; v != -1; v = Heavy_[v]) {
          Root_[v] = u;
          TreePos_[v] = currentPos++;
        }
      }
    }
  }

  template <typename F>
  auto Modify(const int v, F&& f) {
    Modify(v, v, std::move(f));
  }

  template <typename F>
  auto Modify(const int u, const int v, F&& f) { // [u, v]
    ProcessPath(u, v, [f = std::move(f)](const int l, const int r) {
      f(l, r); // [l, r)
    });
  }

  template <typename F>
  auto Query(const int u, const int v, F&& f) { // [u, v]
    ProcessPath(u, v, std::move(f));
  }

  auto Pos(const int v) const {
    assert(std::clamp(v, 0, N_ - 1) == v);
    return TreePos_[v];
  }

 private:
  template<typename BinaryOP>
  void ProcessPath(int u, int v, BinaryOP&& op) {
    for (; Root_[u] != Root_[v]; v = Parent_[Root_[v]]) {
      if (Depth_[Root_[u]] > Depth_[Root_[v]]) {
        std::swap(u, v); // u closer to lca rather than v
      }
      op(TreePos_[Root_[v]], TreePos_[v] + 1);
    }
    if (Depth_[u] > Depth_[v]) {
      std::swap(u, v);
    }
    op(TreePos_[u], TreePos_[v] + 1);
  }

  template<typename G>
  auto Dfs(const G &g, const int v) -> int {
    auto size = 1, maxSubtree = 0;
    for (auto u : g[v]) {
      if (u == Parent_[v]) {
        continue;
      }
      Parent_[u] = v;
      Depth_[u] = Depth_[v] + 1;
      auto subtree = Dfs(g, u);
      if (subtree > maxSubtree) {
        Heavy_[v] = u;
        maxSubtree = subtree;
      }
      size += subtree;
    }
    return size;
  }

 private:
  const int N_ = 0;
  std::vector<int> Parent_, Root_, Depth_, TreePos_, Heavy_;
};