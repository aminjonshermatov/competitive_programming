#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = long long;

int slow(vector<int> &A) {
  const int n(A.size());
  i64 bal = 0;
  for (int i = 0; i + 1 < n; ++i) {
    bal += abs(A[i] - A[i + 1]);
  }
  int ans = n;
  for (int mask = 0; mask < (1 << n); ++mask) {
    i64 loc = 0, prv = -1;
    for (int i = 0; i < n; ++i) {
      if ((mask >> (n - i - 1)) & 1) {
        if (prv != -1) {
          loc += abs(A[i] - prv);
        }
        prv = A[i];
      }
    }
    if (loc == bal) {
      ans = min(ans, __builtin_popcount(mask));
    }
  }
  return max(1, ans);
}

int fast(vector<int> &A) {
  const int n(A.size());
  for (auto &a : A) ++a;
  map<int, int> cnt{};
  for (int i = 0; i + 1 < n; ++i) {
    if (A[i] >= A[i + 1]) {
      ++cnt[A[i]];
      ++cnt[-A[i + 1]];
    } else {
      ++cnt[-A[i]];
      ++cnt[A[i + 1]];
    }
  }
  for (auto a : A) {
    if (cnt[a] >= cnt[-a]) {
      cnt[a] -= cnt[-a];
      cnt[-a] = 0;
    } else {
      cnt[-a] -= cnt[a];
      cnt[a] = 0;
    }
  }
  int ans = 0;
  for (auto [k, v] : cnt) {
    if (v != 0) {
      if (k > 0) {
        ans += max(1, v / 2);
      } else {
        ans += (v + 1) / 2;
      }
    }
    dbg(k, v);
  }
  dbg(ans);
  return min(n, max(1, ans));
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

void test() {
  for (int _ = 0; _ < 10; ++_) {
    int n = 1 + abs(int(rnd())) % 6;
    vector<int> A(n);
    for (auto &a : A) {
      a = abs(int(rnd())) % 10;
    }
    auto a = slow(A);
    auto b = fast(A);
    if (a != b) {
      dbg(a, b, A);
    }
  }
  exit(0);
}

void solve() {
  //test();
  int n; cin >> n;
  vector<int> A(n);
  for (auto &a : A) cin >> a;
  cout << fast(A) << '\n';
  exit(0);
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
