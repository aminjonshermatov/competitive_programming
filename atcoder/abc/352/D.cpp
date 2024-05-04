#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&&... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&&... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&&... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

template <typename Node> struct SparseTable {
  std::vector<std::vector<Node>> table;

  template <typename U> explicit SparseTable(const std::vector<U>& init_) { init(init_); }

  template <typename U> auto init(const std::vector<U>& init_) -> void {
    table.assign(init_.size(), {});
    for (auto i = 0u; i < init_.size(); ++i) {
      table[i].emplace_back(init_[i]);
    }
    for (auto l = 1u, j = 0u; 2 * l <= init_.size(); ++j, l <<= 1) {
      for (auto i = 0u; i + 2 * l <= init_.size(); ++i) {
        table[i].emplace_back(Node::unite(table[i][j], table[i + l][j]));
      }
    }
  }

  [[nodiscard]] decltype(auto) query(int l, int r) const {
    const auto b = 31 - __builtin_clz(r - l);
    return Node::unite(table[l][b], table[r - (1 << b)][b]);
  }
};

constexpr auto inf = std::numeric_limits<int>::max() / 2;
struct Node {
  int min = inf, max = -inf;
  explicit Node(int x) : min(x), max(x) { }
  Node(int a, int b) : min(a), max(b) { }
  static Node unite(const Node& a, const Node& b) {
    return {std::min(a.min, b.min), std::max(a.max, b.max)};
  }
};

void solve() {
  int n, k;
  scan(n, k);
  std::vector<int> ps(n);
  for (auto&& p : ps) {
    scan(p);
  }

  std::vector<int> pos(n);
  for (int i = 0; i < n; ++i) {
    pos[ps[i] - 1] = i;
  }
  SparseTable<Node> rmq(pos);
  int best = n - 1;
  for (int l = 0, r = k; r <= n; ++l, ++r) {
    const auto [min, max] = rmq.query(l, r);
    best = std::min(best, max - min);
  }
  println(best);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}