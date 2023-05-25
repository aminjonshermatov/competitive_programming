#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;
constexpr auto inf = numeric_limits<i64>::max();

i64 fast1(int n, int k, vector<int> A) {
  vector<int> id(n);
  iota(id.begin(), id.end(), 0);
  sort(id.begin(), id.end(), [&A](int i, int j) {
    if (A[i] == A[j]) return i > j;
    return A[i] < A[j];
  });

  vector<i64> left(k);
  id.resize(k);
  sort(id.begin(), id.end());
  for (int i = 0; i < k; ++i) {
    left[i] = A[id[i]];
  }

  i64 rhs = accumulate(left.begin(), left.end(), 0ll);
  i64 lhs = 0, ans = rhs;
  for (int i = 0; i < k; ++i) {
    lhs += A[id[i]];
    rhs -= A[id[i]];
    ans = min(ans, max(lhs, rhs));
  }
  return ans;
}

i64 fast2(int n, int k, vector<int> A) {
  vector<int> id(n);
  iota(id.begin(), id.end(), 0);
  sort(id.begin(), id.end(), [&A](int i, int j) {
    if (A[i] == A[j]) return i < j;
    return A[i] < A[j];
  });

  vector<i64> left(k);
  id.resize(k);
  sort(id.begin(), id.end());
  for (int i = 0; i < k; ++i) {
    left[i] = A[id[i]];
  }

  i64 rhs = accumulate(left.begin(), left.end(), 0ll);
  i64 lhs = 0, ans = rhs;
  for (int i = 0; i < k; ++i) {
    lhs += A[id[i]];
    rhs -= A[id[i]];
    ans = min(ans, max(lhs, rhs));
  }
  return ans;
}

i64 slow(int n, int k, vector<int> A) {
  i64 ans = inf;
  for (int mask = 0; mask < (1 << n); ++mask) {
    if (__builtin_popcount(mask) == k) {
      vector<int> nums;
      for (int i = 0; i < n; ++i) {
        if (mask >> i & 1) nums.emplace_back(A[i]);
      }
      i64 rhs = accumulate(nums.begin(), nums.end(), 0ll);
      i64 lhs = 0, loc = rhs;
      for (int i = 0; i < k; ++i) {
        lhs += nums[i];
        rhs -= nums[i];
        loc = min(loc, max(lhs, rhs));
      }
      ans = min(ans, loc);
    }
  }
  return ans;
}

// #define DEBUG

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> range(1, 15);

void solve() {
#ifndef DEBUG
  int n, k; cin >> n >> k;
  vector<int> A(n);
  for (auto &a : A) cin >> a;
#else
  int n, k;
  n = range(rnd);
  do {
    k = range(rnd);
  } while (k > n);

  vector<int> A(n);
  std::generate(A.begin(), A.end(), bind(range, ref(rnd)));
#endif

  auto f = min(fast1(n, k, A), fast2(n, k, A));
#ifdef DEBUG
  auto s = slow(n, k, A);
  if (f != s) {
    dbg(n, k, A);
    dbg(f, s);
    exit(1);
  }
  exit(0);
#else
  cout << f << '\n';
#endif
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
