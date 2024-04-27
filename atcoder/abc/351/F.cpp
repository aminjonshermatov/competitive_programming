#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&&... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&&... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&&... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

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

using i64 = int64_t;
struct Node {
  i64 sum = 0;
  int cnt = 0;
  static Node unite(const Node& a, const Node& b) {
    return {a.sum + b.sum, a.cnt + b.cnt};
  }
};

void solve() {
  int n;
  scan(n);
  std::vector<i64> as(n);
  for (auto&& a : as) {
    scan(a);
  }
  auto as_sorted = as;
  std::ranges::sort(as_sorted);
  as_sorted.erase(std::ranges::unique(as_sorted).begin(), as_sorted.end());
  for (auto& a : as) {
    a = int(std::ranges::lower_bound(as_sorted, a) - as_sorted.begin());
  }
  const auto m = int(as_sorted.size());
  BottomUpSegmentTree<Node> st(m);
  dbg(as);
  i64 tot = 0;
  for (int i = 0; i < n; ++i) {
    const auto [sum, cnt] = st.query(0, as[i]);
    tot += cnt * 1LL * as_sorted[as[i]] - sum;
    const auto [x, y] = st.query(as[i], as[i] + 1);
    st.modify(as[i], {x + as_sorted[as[i]], y + 1});
  }
  println(tot);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}