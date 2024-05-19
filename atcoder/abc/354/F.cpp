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

struct Node {
  int val = 0;
  static Node unite(const Node& a, const Node& b) {
    return {std::max(a.val, b.val)};
  }
};

std::vector<int> lis(const std::vector<int>& xs) {
  const auto n = int(xs.size());
  const auto maxX = std::ranges::max(xs);
  BottomUpSegmentTree<Node> st(maxX + 1);
  std::vector<int> ret(n);
  for (int i = 0; i < n; ++i) {
    auto&& [best] = st.query(0, xs[i]);
    ret[i] = best + 1;
    if (st.query(xs[i], xs[i] + 1).val < ret[i]) {
      st.modify(xs[i], {ret[i]});
    }
  }
  return ret;
}

void solve() {
  int n;
  scan(n);
  std::vector<int> as(n);
  for (auto&& a : as) {
    scan(a);
  }

  auto as_sorted = as;
  std::ranges::sort(as_sorted);
  as_sorted.erase(std::ranges::unique(as_sorted).begin(), as_sorted.end());
  for (auto&& a : as) {
    a = int(std::ranges::lower_bound(as_sorted, a) - as_sorted.begin());
  }

  const auto m = int(as_sorted.size());

  auto&& l2r = lis(as);
  std::ranges::reverse(as);
  std::ranges::transform(as.begin(), as.end(),
                         as.begin(),
                         [m](auto&& x) { return m - x - 1; });
  auto&& r2l = lis(as);
  auto&& L = std::ranges::max(r2l);
  std::vector<int> ids;
  for (int i = 0; i < n; ++i) {
    if (l2r[i] + r2l[n - i - 1] - 1 == L) {
      ids.emplace_back(i);
    }
  }
  println(ids.size());
  for (auto&& id : ids) {
    print(id + 1);
  }
  println();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  scan(t);
  while (t-- > 0) {
    solve();
  }
}