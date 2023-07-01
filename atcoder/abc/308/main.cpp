#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

struct Node {
  Node *go[2]{};
  int cnt;
  Node() {
    go[0] = go[1] = nullptr;
    cnt = 0;
  }
};

void solve() {
  int q; cin >> q;

  auto root = Node();

  auto add = [&](int x) -> void {
    auto cur = &root;
    for (int b = 29; b >= 0; --b) {
      auto d = x >> b & 1;
      if (cur->go[d] == nullptr) {
        cur->go[d] = new Node();
      }
      ++cur->go[d]->cnt;
      cur = cur->go[d];
    }
  };

  auto rmv = [&](int x) -> void {
    auto cur = &root;
    for (int b = 29; b >= 0; --b) {
      auto d = x >> b & 1;
      assert(cur->go[d] != nullptr);
      --cur->go[d]->cnt;
      cur = cur->go[d];
    }
  };

  auto dfs = [&](auto &f, Node *node, int b) -> int {
    if (b < 0) return 0;
    int ans = 1e9;

  };

  while (q--) {
    char cmd; cin >> cmd;
    if (cmd == '1') {
      int x; cin >> x;
      add(x);
    } else if (cmd == '2') {
      int x; cin >> x;
      rmv(x);
    } else if (cmd == '3') {
      cout << dfs(dfs, &root, 29);
    } else {
      assert(false);
    }
  }
}

bool is_multi = false;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
  return 0;
}
