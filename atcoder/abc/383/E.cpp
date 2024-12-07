#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

class DSU {
 public:
  explicit DSU(int n)
    : N_(n), Components(n), Parent_(n), Rank(n, 1)
  {
    std::iota(Parent_.begin(), Parent_.end(), 0);
  }

  [[nodiscard]] int Find(int v) {
    assert(std::clamp(v, 0, N_ - 1) == v);

    while (v != Parent_[v]) {
      v = Parent_[v] = Parent_[Parent_[v]];
    }
    return v;
  }

  bool Merge(int u, int v) {
    assert(std::clamp(u, 0, N_ - 1) == u);
    assert(std::clamp(v, 0, N_ - 1) == v);

    auto pu = Find(u);
    auto pv = Find(v);
    if (pu == pv) {
      return false;
    }

    if (Rank[pu] < Rank[pv]) {
      std::swap(pu, pv);
    }
    Parent_[pv] = pu;
    Rank[pu] += Rank[pv];
    --Components;
    return true;
  }

  [[nodiscard]] bool IsSame(int u, int v) noexcept {
    assert(std::clamp(u, 0, N_ - 1) == u);
    assert(std::clamp(v, 0, N_ - 1) == v);

    return Find(u) == Find(v);
  }

 public:
  int Components{0};
  std::vector<int> Rank;

 private:
  int N_{0};
  std::vector<int> Parent_;
};

void Solve() {
  int n, m, k;
  Scan(n, m, k);
  std::vector<std::tuple<int, int, int>> es(m);
  for (auto& [u, v, w] : es) {
    Scan(u, v, w);
    --u, --v;
  }
  std::vector<std::vector<int>> as(n), bs(n);
  for (int i = 0; i < k; ++i) {
    int v;
    Scan(v);
    --v;
    as[v].emplace_back(v);
  }
  for (int i = 0; i < k; ++i) {
    int v;
    Scan(v);
    --v;
    bs[v].emplace_back(v);
  }

  std::vector<int> ord(m);
  std::iota(ord.begin(), ord.end(), 0);
  std::ranges::sort(ord, [&](int i, int j) {
    return std::get<2>(es[i]) < std::get<2>(es[j]);
  });
  std::vector<int> par(n);
  std::iota(par.begin(), par.end(), 0);
  auto find = [&](auto&& self, int v) -> int {
    while (v != par[v]) {
      v = par[v] = par[par[v]];
    }
    return v;
  };
  auto rank = [&](int v) {
    return as[v].size() + bs[v].size();
  };
  auto merge = [&](int u, int v) -> int {
    auto pu = find(find, u);
    auto pv = find(find, v);
    if (pu == pv) {
      return -1;
    }

    if (rank(pu) < rank(pv)) {
      std::swap(pu, pv);
    }
    par[pv] = pu;
    as[pu].insert(as[pu].end(), as[pv].begin(), as[pv].end());
    as[pv].clear();
    bs[pu].insert(bs[pu].end(), bs[pv].begin(), bs[pv].end());
    bs[pv].clear();
    return pu;
  };

  int64_t tot{0};
  for (int i = 0; i < m; ++i) {
    const auto u = std::get<0>(es[ord[i]]);
    const auto v = std::get<1>(es[ord[i]]);
    const auto w = std::get<2>(es[ord[i]]);
    const auto p = merge(u, v);
    if (p != -1) {
      while (!as[p].empty() && !bs[p].empty()) {
        tot += w;
        as[p].pop_back();
        bs[p].pop_back();
      }
    }
  }
  Println(tot);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
