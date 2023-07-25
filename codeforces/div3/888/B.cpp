#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> as(n);
  vector<int> even, odd;
  for (auto &a : as) {
    cin >> a;
    (a & 1 ? odd : even).emplace_back(a);
  }
  sort(even.begin(), even.end());
  reverse(even.begin(), even.end());
  sort(odd.begin(), odd.end());
  reverse(odd.begin(), odd.end());
  vector<int> ans(n);
  for (int i = 0; i < n; ++i) {
    if (as[i] & 1) {
      assert(!odd.empty());
      ans[i] = odd.back();
      odd.pop_back();
    } else {
      assert(!even.empty());
      ans[i] = even.back();
      even.pop_back();
    }
  }
  cout << (is_sorted(ans.begin(), ans.end()) ? "Yes" : "No") << '\n';
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
