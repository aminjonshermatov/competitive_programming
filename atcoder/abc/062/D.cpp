#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n; cin >> n;
  vector<int64_t> A(3 * n);
  for (auto &a : A) cin >> a;

  vector<int64_t> left(3 * n, 0), right(3 * n, 0);
  {
    priority_queue<int64_t, vector<int64_t>, greater<>> pq;
    int64_t cur = 0;
    for (int i = 0; i < 3 * n; ++i) {
      pq.emplace(A[i]);
      cur += A[i];
      if (pq.size() > n) {
        cur -= pq.top();
        pq.pop();
      }
      left[i] = cur;
    }
  }
  {
    priority_queue<int64_t> pq;
    int64_t cur = 0;
    for (int i = 3 * n - 1; i >= 0; --i) {
      pq.emplace(A[i]);
      cur += A[i];
      if (pq.size() > n) {
        cur -= pq.top();
        pq.pop();
      }
      right[i] = cur;
    }
  }
  dbg(left);
  dbg(right);
  auto ans = numeric_limits<int64_t>::min();
  for (int i = n - 1; i < 2 * n; ++i) {
    ans = max(ans, left[i] - right[i + 1]);
  }
  cout << ans << '\n';
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
