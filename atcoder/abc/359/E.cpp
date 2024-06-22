#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&&... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&&... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&&... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

template <typename Node>
struct SparseTable {
  std::vector<std::vector<Node>> table;

  template <typename U>
  explicit SparseTable(const std::vector<U>& init_) { init(init_); }

  template <typename U>
  void init(const std::vector<U>& init_) {
    table.resize(init_.size());
    for (std::size_t i{}; i < init_.size(); ++i) {
      table[i].emplace_back(init_[i]);
    }
    for (std::size_t l{1}, j{}; 2 * l <= init_.size(); ++j, l <<= 1u) {
      for (std::size_t i{}; i + 2 * l <= init_.size(); ++i) {
        table[i].emplace_back(Node::unite(std::forward<Node>(table[i][j]),
                                          std::forward<Node>(table[i + l][j])));
      }
    }
  }

  [[nodiscard]] Node query(std::size_t l, std::size_t r) const {
    const auto b = std::__lg(r - l);
    return Node::unite(table[l][b], table[r - (1 << b)][b]);
  }
};

constexpr auto inf = std::numeric_limits<int>::max() / 2;
struct Node {
  int val = -inf, idx = -1;
  static Node unite(auto&& a, auto&& b) {
    if (a.val == b.val) {
      return a.idx > b.idx ? a : b;
    }
    return a.val > b.val ? a : b;
  }
};

using i64 = int64_t;

void solve() {
  int n;
  scan(n);
  std::vector<i64> hs(n + 1);
  for (int i = 0; i < n; ++i) {
    scan(hs[i]);
  }
  hs[n] = 0;

  std::vector<Node> init(n);
  for (int i = 0; i < n; ++i) {
    init[i] = {static_cast<int>(hs[i]), i};
  }
  const auto rmq = SparseTable<Node>(init);

  std::vector<i64> ret(n + 1), dp(n + 1);
  ret[0] = 0;
  dp[0] = hs[0];
  for (int i = 1; i <= n; ++i) {
    const auto [max, idx] = rmq.query(0, i);
    ret[i] = dp[i - 1] + 1;
    if (max > hs[i]) {
      int lo = idx, hi = i;
      while (hi - lo > 1) {
        const auto mid = lo + (hi - lo) / 2;
        (rmq.query(mid, i).val >= hs[i] ? lo : hi) = mid;
      }
      assert(hs[lo] >= hs[i]);
      dbg("max",i,lo,dp[i-1],hs[i],i-lo);
      dp[i] += dp[lo] + hs[i] * (i - lo);
    } else {
      dbg("oth",i,idx,dp[i-1],hs[idx],i-idx,hs[i]-hs[idx]);
      dp[i] += hs[i] * (i + 1);
    }
  }
  dbg(ret);
  dbg(dp);
  for (int i = 1; i <= n; ++i) {
    print(ret[i]);
  }
  println();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}