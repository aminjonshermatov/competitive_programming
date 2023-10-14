#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  int n;
  cin >> n;
  string t;
  cin >> t;
  t.push_back('#');
  const auto nn = int(t.size());
  vector<int> ids;
  for (int id = 0; id < n; ++id) {
    string s;
    cin >> s;
    s.push_back('#');
    const auto mm = int(s.size());
    int i = 0, j = 0;
    bool ok = true, used = false;
    while (i < nn && j < mm) {
      if (t[i] == s[j]) {
        ++i, ++j;
      } else if (!used && (nn - i) > (mm - j)) {
        used = true;
        i += 1;
      } else if (!used && (nn - i) < (mm - j)) {
        used = true;
        j += 1;
      } else if (!used) {
        used = true;
        i += 1;
        j += 1;
      } else {
        ok = false;
        break;
      }
    }
    if (ok) {
      ids.emplace_back(id + 1);
    }
  }
  cout << ids.size() << '\n';
  for (auto id : ids) {
    cout << id << ' ';
  }
  cout << '\n';
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
