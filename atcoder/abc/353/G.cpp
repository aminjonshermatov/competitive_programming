#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&&... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&&... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&&... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

using i64 = int64_t;

template <typename Node> struct BottomUpSegmentTree {
  int n = 0;
  std::vector<Node> nodes;

  BottomUpSegmentTree() = default;
  explicit BottomUpSegmentTree(int n_) { init(std::vector(n_, Node())); }
  BottomUpSegmentTree(int n_, const Node& node) { init(std::vector(n_, node)); }
  template <typename T> explicit BottomUpSegmentTree(const std::vector<T>& init_) { init(init_); }

  template <typename T> void init(const std::vector<T>& init_) {
    for (n = 1; n < init_.size(); n *= 2) { }
    nodes.assign(2 * n, Node());
    for (int i = 0; i < init_.size(); ++i) {
      nodes[i + n] = Node(init_[i]);
    }
    for (int i = n - 1; i >= 1; --i) {
      nodes[i] = Node::unite(nodes[i << 1], nodes[i << 1 | 1]);
    }
  }

  void modify(int pos, const Node& val) {
    nodes[pos += n] = val;
    for (pos >>= 1; pos >= 1; pos >>= 1) {
      nodes[pos] = Node::unite(nodes[pos << 1], nodes[pos << 1 | 1]);
    }
  }
  Node query(int l, int r) {
    auto retL = Node(), retR = Node();
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) {
        retL = Node::unite(retL, nodes[l++]);
      }
      if (r & 1) {
        retR = Node::unite(nodes[--r], retR);
      }
    }
    return Node::unite(retL, retR);
  }
};

constexpr auto kInf = std::numeric_limits<i64>::max() / 10;
struct Node {
  i64 val = -kInf;
  static Node unite(const Node& a, const Node& b) {
    return {std::max(a.val, b.val)};
  }
};

bool imax(auto&& a, auto&& b) {
  return (a < b) && (a = b, true);
}

void solve() {
  int n, m;
  i64 c;
  scan(n, c, m);
  std::vector<int> ts(m + 1);
  std::vector<i64> ps(m + 1);
  for (int i = 1; i <= m; ++i) {
    scan(ts[i], ps[i]);
    --ts[i];
  }

  BottomUpSegmentTree<Node> dpL(n), dpR(n);
  dpL.modify(0, {0});
  dpR.modify(0, {0});
  auto at = [&](bool isR, int b) {
    return !isR ? dpL.query(b, b + 1).val : dpR.query(b, b + 1).val;
  };
  for (int i = 1; i <= m; ++i) {
    // ts[j] <= ts[i]
    // | dp[ts[j]] - c*ts[j] + c*ts[i] + ps[i]
    // ts[j] > ts[i]
    // | dp[ts[j]] + c*ts[j] - c*ts[i] + ps[i]
    const auto dpi = std::max(dpL.query(0, ts[i] + 1).val + -c * ts[i], dpR.query(ts[i], n).val + c * ts[i]);
    dpL.modify(ts[i], {std::max(at(false, ts[i]), dpi + c * ts[i] + ps[i])});
    dpR.modify(ts[i], {std::max(at(true, ts[i]), dpi - c * ts[i] + ps[i])});
  }
  auto best = -kInf;
  for (int i = 0; i < n; ++i) {
    imax(best, dpL.query(i, i + 1).val - c * i);
    imax(best, dpR.query(i, i + 1).val + c * i);
  }
  println(best);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}