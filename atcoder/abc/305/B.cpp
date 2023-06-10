#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  map<char, int> dist{
    {'A', 3},
    {'B', 1},
    {'C', 4},
    {'D', 1},
    {'E', 5},
    {'F', 9}
  };

  char a, b; cin >> a >> b;
  tie(a, b) = tuple(min(a, b), max(a, b));
  int ans = 0;
  for (auto it = dist.find(a); it != dist.end() && it->first != b; ++it) {
    ans += it->second;
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
