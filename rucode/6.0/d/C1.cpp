//
// Created by aminjon on 3/20/23.
//
#include <bits/stdc++.h>

using namespace std;

inline constexpr int MOD = 1e9 + 7;

int add(int a, int b) {
  return int(((0ll + a + b) % MOD + MOD) % MOD);
}
int mult(int a, int b) {
  return int(((1ll * a * b) % MOD + MOD) % MOD);
}

void solve() {
  int n; cin >> n;
  vector<int> A(n);
  for (auto &a : A) cin >> a;

  vector<int> fact(n);
  fact[0] = 1;
  for (int i = 1; i < n; ++i) {
    fact[i] = fact[i - 1] * i;
  }

  int ans = 1;
  for (int i = 0; i < n; ++i) {
    int inv = 0;
    for (int j = i + 1; j < n; ++j) {
      inv += A[i] > A[j];
    }
    ans = add(ans, mult(inv, fact[n - i - 1]));
  }

  cout << ans << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  solve();
}