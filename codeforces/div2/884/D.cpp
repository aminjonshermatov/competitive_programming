#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

inline char nxt(char ch, int mx = 26) {
  return char('a' + (ch - 'a' + 1) % mx);
}

void solve() {
  int n; cin >> n;

  vector<int> cs;
  cs.emplace_back(1);
  for (int c = 2; c * c <= n; ++c) {
    auto [q, r] = div(n, c);
    if (r != 0) continue;
    cs.emplace_back(c);
    if (q != c) {
      cs.emplace_back(q);
    }
  }

  sort(cs.begin(), cs.end());
  cs.resize(unique(cs.begin(), cs.end()) - cs.begin());
  int mx = -1;
  for (int i = 0; i < n; ++i) {
    int loc = 0;
    for (auto c : cs) {
      loc += i + c < n;
    }
    mx = max(mx, loc);
  }
  ++mx;

  string s(n, 'a');
  dbg(mx);
  for (int i = 0; i < n; ++i) {
    for (auto c : cs) {
      if (i + c < n && s[i] == s[i + c]) {
        s[i + c] = nxt(s[i], mx);
      }
    }
  }
  cout << s << '\n';
}

bool is_multi = true;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
  return 0;
}
