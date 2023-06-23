#include <bits/stdc++.h>
#include <nlohmann/json.hpp>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;
using json = nlohmann::json;

void solve() {
  vector<string> names = json::parse(cin)["names"];
  sort(names.begin(), names.end());
  int64_t sm = 0;
  for (size_t i = 0; i < names.size(); ++i) {
    int ord_sm = 0;
    for (auto ch : names[i]) {
      ord_sm += ch - 'A' + 1;
    }
    sm += int64_t(ord_sm) * (i + 1);
  }
  cout << sm << '\n';
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
