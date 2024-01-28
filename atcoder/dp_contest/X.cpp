#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using i64 = int64_t;

void solve() {
  int n;
  std::cin >> n;
  std::vector<i64> W(n), S(n), V(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> W[i] >> S[i] >> V[i];
  }
  auto max = std::ranges::max(S) + std::ranges::max(W);
  std::vector<i64> dp(max + 1, -1);
  std::vector<int> ord(n);
  std::iota(ord.begin(), ord.end(), 0);
  std::ranges::sort(ord, [&](int i, int j) {
    return S[i] + W[i] < S[j] + W[j];
  });
  dbg(max);
  dbg(ord);
  dp[0] = 0;
  for (auto i : ord) {
    auto ndp = dp;
    for (auto w = 0; w <= S[i]; ++w) {
      auto nw = w + W[i];
      if (nw > max || dp[w] == -1) {
        continue;
      }
      ndp[nw] = std::max(ndp[nw], dp[w] + V[i]);
    }
    dp.swap(ndp);
  }
  std::cout << std::ranges::max(dp) << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
