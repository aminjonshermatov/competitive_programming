#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n;
  cin >> n;
  vector<int> as(n);
  for (auto &a : as) {
    cin >> a;
  }
  for (int &a : as) {
    if (a == *min_element(as.begin(), as.end())) {
      ++a;
      break;
    }
  }
  int64_t p = 1;
  for (auto a : as) {
    p *= a;
  }
  cout << p << '\n';
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
