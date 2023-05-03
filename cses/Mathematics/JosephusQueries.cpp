// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

int solve(int n, int k) {
  if (n == 1) return 1;
  auto this_ring = (n + 1) / 2;
  if (k <= this_ring) {
    return 2 * k > n ? 2 * k % n : 2 * k;
  }
  auto nk = solve(n / 2, k - this_ring);
  return 2 * nk + (n % 2 == 1 ? 1 : - 1);
}

int slow(int n, int k) {
  vector<int> A(n);
  iota(A.begin(), A.end(), 1);
  vector<bool> used(n, false);
  vector<int> ans(k + 1);
  for (int i = 1, j = 1; i <= k; ++i) {
    ans[i] = A[j];
    used[j] = true;
    while (i < k && used[(j + 1) % n]) ++j;
    j = (j + 1) % n;
    while (i < k && used[(j + 1) % n]) ++j;
    j = (j + 1) % n;
  }
  return ans[k];
}

random_device rd;
mt19937 rnd(rd());
uniform_int_distribution<int> distN(2, 10);
uniform_int_distribution<int> distK(1, 10);

void check(int N) {
  for (int _ = 0; _ < N; ++_) {
    auto n = distN(rnd);
    auto k = distK(rnd);
    if (k > n) continue;
    auto s = slow(n, k);
    auto f = solve(n, k);
    if (s != f) {
      cout << n << ' ' << k << ' ' << s << ' ' << f << '\n';
    }
  }
}

bool is_multi = true;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  /*check(10);
  return 0;*/

  int q; cin >> q;
  for (int i = 0; i < q; ++i) {
    int n, k; cin >> n >> k;
    cout << solve(n, k) << '\n';
  }
}
