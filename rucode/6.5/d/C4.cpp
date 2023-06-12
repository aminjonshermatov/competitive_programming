#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

constexpr int K = 26;

struct Node {
  array<Node*, K> go{};
  int cnt;
  Node() : cnt(0) { go.fill(nullptr); }
};

void solve() {
  auto root = Node();
  auto check = [&](string_view s, int len) -> bool {
    const int n(s.size());
    for (int i = 0; i < len; ++i) {
      if (s[i] != s[n - len + i]) {
        return false;
      }
    }
    return true;
  };
  auto add = [&](string_view s) -> void {
    const int n(s.size());
    auto cur = &root;
    for (int i = 0; i < n; ++i) {
      if (cur->go[s[i] - 'a'] == nullptr) {
        cur->go[s[i] - 'a'] = new Node();
      }
      cur = cur->go[s[i] - 'a'];
      cur->cnt += check(s, i + 1);
    }
  };

  auto get = [&](string_view s) -> int {
    auto cur = &root;
    for (auto ch : s) {
      if (cur->go[ch - 'a'] == nullptr) return 0;
      cur = cur->go[ch - 'a'];
    }
    return cur->cnt;
  };

  int n; cin >> n;
  for (int i = 0; i < n; ++i) {
    string s; cin >> s;
    add(s);
  }

  int m; cin >> m;
  for (int i = 0; i < m; ++i) {
    string t; cin >> t;
    cout << get(t) << '\n';
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
