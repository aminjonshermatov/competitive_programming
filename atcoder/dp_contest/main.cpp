#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

template <typename Node> struct BottomUpSegmentTree {
  int n = 0;
  std::vector<Node> nodes;

  explicit BottomUpSegmentTree(int n_) { init(std::vector(n_, Node())); }
  explicit BottomUpSegmentTree(int n_, Node node) { init(std::vector(n_, node)); }
  template <typename T> explicit BottomUpSegmentTree(std::vector<T> init_) { init(init_); }

  template <typename T> void init(std::vector<T> init_) {
    n = init_.size();
    nodes.assign(2 * init_.size(), Node());
    for (int i = 0; i < init_.size(); ++i) {
      modify(i, Node{init_[i]});
    }
  }

  void modify(int pos, Node val) {
    pos += n;
    nodes[pos] = val;
    while (pos > 1) {
      pos >>= 1;
      nodes[pos] = Node::unite(nodes[pos << 1], nodes[pos << 1 | 1]);
    }
  }
  Node query(int ql, int qr) {
    ql += n; qr += n;
    auto ans = Node();
    while (ql < qr) {
      if (ql & 1) ans = Node::unite(ans, nodes[ql++]);
      if (qr & 1) ans = Node::unite(ans, nodes[--qr]);
      ql >>= 1;
      qr >>= 1;
    }
    return ans;
  }
};

using i64 = int64_t;

struct Node {
  i64 val = 0;
  static Node unite(Node a, Node b) {
    return Node{std::max(a.val, b.val)};
  }
};

void solve() {
  int n;
  std::cin >> n;
  std::vector<int> hs(n), bs(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> hs[i];
  }
  for (int i = 0; i < n; ++i) {
    std::cin >> bs[i];
  }

  auto hs_sorted = hs;
  hs_sorted.emplace_back(std::numeric_limits<int>::max());
  std::sort(hs_sorted.begin(), hs_sorted.end());
  std::unique(hs_sorted.begin(), hs_sorted.end());
  for (auto &h : hs) {
    h = int(std::lower_bound(hs_sorted.begin(), hs_sorted.end(), h) - hs_sorted.begin());
  }

  BottomUpSegmentTree<Node> dp(n + 1);
  for (int i = n - 1; i >= 0; --i) {
    dp.modify(hs[i], {std::max(dp.query(hs[i], hs[i] + 1).val, dp.query(hs[i] + 1, n + 1).val + bs[i])});
  }
  std::cout << dp.query(0, n + 1).val << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
