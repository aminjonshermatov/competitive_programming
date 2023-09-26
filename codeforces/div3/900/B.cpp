#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

const int N = 1e7, M = 2e5 + 10;
bool is_p[N];
int ans[M];

void solve() {
  int n;
  cin >> n;

  for (int i = 0; i < n; ++i) {
    cout << ans[i] << ' ';
  }
  cout << '\n';
}

bool is_multi = true;

int main() {
  memset(is_p, 1, sizeof(is_p));
  for (int i = 2; i < N; ++i) {
    if (!is_p[i]) continue;
    for (int j = i * 2; j < N; j += i) {
      is_p[j] = false;
    }
  }

  for (int i = 0, x = 5; i < M; ++x) {
    if (is_p[x]) {
      ans[i++] = x;
      if (i >= 2) {
        assert((3 * x) % (ans[i - 2] + ans[i - 3]) != 0);
      }
    }
  }

  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
  return 0;
}
