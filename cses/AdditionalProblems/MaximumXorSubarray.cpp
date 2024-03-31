#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

struct Node {
  std::array<int, 2> go{};
  Node() {
    go.fill(-1);
  }
};

void solve() {
  int n;
  std::cin >> n;
  std::vector<int> as(n);
  for (auto& a : as) {
    std::cin >> a;
  }
  const int B = 32 - __builtin_clz(*std::max_element(as.begin(), as.end()));
  dbg(as);
  std::vector<Node> nodes;
  const int root = 0;
  nodes.emplace_back();
  auto add = [&](int x) -> void {
    int cur = root;
    for (int ib = B - 1; ib >= 0; --ib) {
      const int b = x >> ib & 1;
      if (nodes[cur].go[b] == -1) {
        nodes[cur].go[b] = int(nodes.size());
        nodes.emplace_back();
      }
      cur = nodes[cur].go[b];
    }
  };
  auto qry = [&](int x) -> int {
    int cur = root, ret = 0;
    for (int ib = B - 1; ib >= 0; --ib) {
      int b = x >> ib & 1;
      if (nodes[cur].go[1 ^ b] != -1) {
        ret |= 1 << ib;
      } else {
        b ^= 1;
      }
      cur = nodes[cur].go[1 ^ b];
    }
    return ret;
  };
  add(0);
  int pf = 0, best = 0;
  for (int i = 0; i < n; ++i) {
    pf ^= as[i];
    best = std::max(best, qry(pf));
    add(pf);
  }
  std::cout << best << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}