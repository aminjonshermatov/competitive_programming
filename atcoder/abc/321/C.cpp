#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  int k;
  cin >> k;
  vector<vector<string>> prv(10);
  for (int i = 0; i < 10; ++i) {
    prv[i].emplace_back(to_string(i));
    if (i == k) {
      cout << to_string(i) << '\n';
      return;
    }
  }
  k -= 9;
  dbg(prv);
  for (int len = 2; ; ++len) {
    vector<vector<string>> cur(10);
    for (int x = 0; x < 10; ++x) {
      for (int y = 0; y < x; ++y) {
        for (auto ns : prv[y]) {
          reverse(ns.begin(), ns.end());
          ns.push_back(char('0' + x));
          reverse(ns.begin(), ns.end());
          if (ns.size() == len) {
            --k;
            cur[x].emplace_back(ns);
            if (0 == k) {
              cout << ns << '\n';
              return;
            }
          }
        }
      }
    }
    dbg(cur.size());
    prv.swap(cur);
  }
  assert(false);
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
