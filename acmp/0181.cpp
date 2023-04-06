// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using u64 = ::uint64_t ;

void solve() {
  map<char, string> rule;
  for (auto dir : {'N', 'S', 'W', 'E', 'U', 'D'}) {
    string cmds;
    getline(cin, cmds);
    rule[dir] = cmds;
  }

  map<pair<char, int>, u64> cache;
  auto dfs = [&](auto f, char x, int k) -> u64 {
    u64 ans = 1;
    if (k == 1) return ans;
    if (cache.count(pair(x, k)) > 0) return cache[pair(x, k)];
    for (auto nx : rule[x]) ans += f(f, nx, k - 1);
    return cache[pair(x, k)] = ans;
  };

  char x; int k;
  cin >> x >> k;
  cout << dfs(dfs, x, k) << '\n';
}

//#define MEASURE_TIME
bool is_multi = false;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
#ifdef MEASURE_TIME
  auto start = chrono::steady_clock::now();
#endif
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
#ifdef MEASURE_TIME
  auto finish = chrono::steady_clock::now();
  auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(finish - start);
  cerr << endl << "Time: " << elapsed_ms.count() << " ms\n";
#endif
  return 0;
}