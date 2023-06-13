#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

struct Node {
  array<Node*, 2> go{};
  Node() { go.fill(nullptr); }
};

void solve() {
  int n; cin >> n;

  Node root;
  auto add = [&](int x) -> void {
    auto cur = &root;
    for (int i = 30; i >= 0; --i) {
      auto b = x >> i & 1;
      if (cur->go[b] == nullptr) {
        cur->go[b] = new Node();
      }
      cur = cur->go[b];
    }
  };
  vector<int> as(n);
  for (auto &a : as) {
    cin >> a;
    add(a);
  }

  auto dfs = [&](auto &f, Node *cur, int b) -> int {
    assert(cur != nullptr);
    int loc = 0;
    if (cur->go[0] != nullptr && cur->go[1] != nullptr) {
      loc = max(1 << b | f(f, cur->go[0], b - 1), f(f, cur->go[1], b - 1));
    } else if (cur->go[0] != nullptr) {
      loc = f(f, cur->go[0], b - 1);
    } else if (cur->go[1] != nullptr) {
      loc = f(f, cur->go[1], b - 1) | 1 << b;
    }
    return loc;
  };

  int ans = 0;
  auto tmp = dfs(dfs, &root, 30);
  dbg(tmp);
  for (auto a : as) {
    ans = max(ans, a ^ tmp);
  }
  cout << ans << '\n';
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
