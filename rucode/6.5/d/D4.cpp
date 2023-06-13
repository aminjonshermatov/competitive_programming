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
  vector<int> as(n);
  for (auto &a : as) cin >> a;
  Node *root;
  auto add = [&](int x, bool is_special = false) -> void {
    auto cur = root;
    for (int i = 30; i >= 0 && (x > 0 || is_special); --i) {
      auto ib = x >> i & 1;
      if (cur->go[ib] == nullptr) {
        cur->go[ib] = new Node();
      }
      cur = cur->go[ib];
    }
  };
  auto qry = [&](int x) -> int {
    auto cur = root;
    int ans = 0;
    for (int i = 30; i >= 0 && cur != nullptr; --i) {
      auto ib = x >> i & 1;
      if (cur->go[1 ^ ib] != nullptr) {
        ans |= 1 << i;
        cur = cur->go[1 ^ ib];
      } else {
        cur = cur->go[ib];
      }
    }
    return ans;
  };

  vector<int> dp_pf(n, 0), dp_sf(n, 0);
  {
    root = new Node();
    int pf = 0;
    add(pf, true);
    for (int i = 0; i < n; ++i) {
      pf ^= as[i];
      dp_pf[i] = qry(pf);
      if (i > 0) {
        dp_pf[i] = max(dp_pf[i], dp_pf[i - 1]);
      }
      add(pf);
    }
  }
  {
    root = new Node();
    int sf = 0;
    add(sf, true);
    for (int i = n - 1; i >= 0; --i) {
      sf ^= as[i];
      dp_sf[i] = qry(sf);
      if (i + 1 < n) {
        dp_sf[i] = max(dp_sf[i], dp_sf[i + 1]);
      }
      add(sf);
    }
  }

  dbg(dp_pf);
  dbg(dp_sf);
  int ans = 0;
  for (int i = 0; i + 1 < n; ++i) {
    ans = max(ans, dp_pf[i] + dp_sf[i + 1]);
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
