#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int two_headed, three_headed;
  cin >> two_headed >> three_headed;
  int one_headed = 2 * two_headed + 3 * three_headed;

  vector<vector<vector<int8_t>>> cache(one_headed + 1, vector<vector<int8_t>>(two_headed + three_headed + 1, vector<int8_t>(three_headed + 1, -1)));
  auto dp = [&](auto &f, int one, int two, int three) -> bool {
    auto s = one + two + three;
    if (s == 0) return false;
    if (s == 1) return true;
    if (~cache[one][two][three]) return cache[one][two][three];

    bool loc = false;
    if (one > 0) {
      loc |= !f(f, one - 1, two, three);
    }
    if (two > 0) {
      loc |= !f(f, one + 1, two - 1, three);
      loc |= !f(f, one, two - 1, three);
    }
    if (three > 0) {
      loc |= !f(f, one, two, three - 1);
      loc |= !f(f, one, two + 1, three - 1);
      loc |= !f(f, one + 1, two, three - 1);
    }
    return cache[one][two][three] = loc;
  };
  cout << 2 - dp(dp, 0, two_headed, three_headed) << '\n';
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
