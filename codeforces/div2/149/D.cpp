#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n; cin >> n;
  string s; cin >> s;
  set<int> open, close;
  for (int i = 0; i < n; ++i) {
    (s[i] == '(' ? open : close).emplace(i);
  }
  dbg(open, close);
  if (open.size() != close.size()) {
    cout << -1 << '\n';
    return;
  }

  vector<int> ans(n, -1);
  int last = 0;
  for (int i = 0; i < n; ++i) {
    if (ans[i] != -1) continue;
    ++last;
    if (s[i] == '(') {
      while (true) {
        auto it_open = open.begin();
        auto it_close = close.upper_bound(*it_open);
        if (it_close == close.end()) break;
        ans[*it_open] = last;
        ans[*it_close] = last;
        open.erase(it_open);
        close.erase(it_close);
      }
    } else {
      while (true) {
        auto it_close = close.begin();
        auto it_open = open.upper_bound(*it_close);
        if (it_open == open.end()) break;
        ans[*it_open] = last;
        ans[*it_close] = last;
        close.erase(it_close);
        open.erase(it_open);
      }
    }
  }
  assert(none_of(ans.begin(), ans.end(), [](int x) { return x == -1; }));
  cout << last << '\n';
  for (auto c : ans) {
    cout << c << ' ';
  }
  cout << '\n';
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
