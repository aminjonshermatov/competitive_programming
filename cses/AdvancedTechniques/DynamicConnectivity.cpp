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
  std::vector<std::tuple<UpdateType, int, int>> history;

  explicit DsuRollback(int n_) : n(n_), components(n), parent(n), rank(n, 1) {
    iota(parent.begin(), parent.end(), 0);
  }

  inline int find(int v) {
    assert(0 <= v && v < n);
    while (v != parent[v]) {
      history.emplace_back(UpdateType::kUpdateParent, v, parent[v]);
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
    history.emplace_back(UpdateType::kUpdateParent, pv, parent[pv]);
    parent[pv] = pu;
    history.emplace_back(UpdateType::kUpdateRank, pu, rank[pu]);
    rank[pu] += rank[pv];
    --components;
    return true;
  }

  inline bool is_same(int u, int v) {
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    return find(u) == find(v);
  }

  [[nodiscard]] std::size_t snapshot() const {
    return history.size();
  }

  void rollback(std::size_t time) {
    for (; history.size() > time;) {
      const auto sz = int(history.size());
      if (sz > 1 && std::get<0>(history[sz - 1]) == UpdateType::kUpdateRank && std::get<0>(history[sz - 2]) == UpdateType::kUpdateParent) {
        rank[std::get<1>(history.back())] = std::get<2>(history.back());
        history.pop_back();
        parent[std::get<1>(history.back())] = std::get<2>(history.back());
        history.pop_back();
        ++components;
      } else if (std::get<0>(history.back()) == UpdateType::kUpdateRank) {
        rank[std::get<1>(history.back())] = std::get<2>(history.back());
        history.pop_back();
      } else if (std::get<0>(history.back()) == UpdateType::kUpdateParent) {
        parent[std::get<1>(history.back())] = std::get<2>(history.back());
        history.pop_back();
      }
      assert(history.size() >= time);
    }
  }
};

void solve() {
  int n, m, q;
  std::cin >> n >> m >> q;
  std::map<std::pair<int, int>, int> time{};
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    if (u-- > v--) {
      std::swap(u, v);
    }
    time[std::pair(u, v)] = 0;
  }

  int qq;
  for (qq = 1; qq < q + 1; qq *= 2) { }
  std::vector<std::vector<std::pair<int, int>>> infos(2 * qq - 1);
  auto add = [&](auto& f, int ql, int qr, const auto& uv, int x, int lx, int rx) -> void {
    if (ql >= rx || qr <= lx) return;
    if (ql <= lx && rx <= qr) {
      infos[x].emplace_back(uv);
      return;
    }
    auto mid = lx + (rx - lx) / 2;
    f(f, ql, qr, uv, 2 * x + 1, lx, mid);
    f(f, ql, qr, uv, 2 * x + 2, mid, rx);
  };
  for (int i = 0; i < q; ++i) {
    int type, u, v;
    std::cin >> type >> u >> v;
    if (u-- > v--) {
      std::swap(u, v);
    }
    auto uv = std::pair(u, v);
    if (type == 1) {
      time[uv] = i + 1;
    } else {
      auto it = time.find(uv);
      assert(it != time.end() && it->second != -1);
      add(add, it->second, i + 1, uv, 0, 0, qq);
      it->second = -1;
    }
  }
  for (auto& [uv, t] : time) {
    if (t != -1) {
      add(add, t, q + 1, uv, 0, 0, qq);
    }
  }

  std::vector<int> ans(q + 1, -1);
  DsuRollback dsu(n);
  auto go = [&](auto& f, int x, int lx, int rx) -> void {
    auto time = dsu.snapshot();
    for (auto [u, v] : infos[x]) {
      dsu.merge(u, v);
    }
    if (rx - lx == 1) {
      if (lx <= q) {
        ans[lx] = dsu.components;
      }
      dsu.rollback(time);
      return;
    }
    auto mid = lx + (rx - lx) / 2;
    f(f, 2 * x + 1, lx, mid);
    f(f, 2 * x + 2, mid, rx);
    dsu.rollback(time);
  };
  go(go, 0, 0, qq);
  for (int i = 0; i <= q; ++i) {
    std::cout << ans[i] << ' ';
  }
  std::cout << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}