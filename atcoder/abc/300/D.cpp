// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

template<typename T>
struct Primes {
  T n;
  vector<T> lp, pr;

  using iterator = typename vector<T>::iterator;
  using const_iterator = typename vector<T>::const_iterator;

  explicit Primes(T n_) : n(n_) {
    lp.assign(n + 1, T(0));
    find_primes();
  }

  auto find_primes() -> void {
    for (T i = 2; i <= n; ++i) {
      if (lp[i] == 0) {
        lp[i] = i;
        pr.push_back(i);
      }
      for (T j = 0; i * pr[j] <= n; ++j) {
        lp[i * pr[j]] = pr[j];
        if (pr[j] == lp[i]) break;
      }
    }
  }

  T operator[](int idx) { return pr[idx]; }
  T &operator[](int idx) const { return pr[idx]; }
  [[nodiscard]] size_t size() const { return pr.size(); }

  iterator begin() { return pr.begin(); }
  [[nodiscard]] const_iterator begin() const { return pr.begin(); }
  iterator end() { return pr.end(); }
  [[nodiscard]] const_iterator end() const { return pr.end(); }
};

using i64 = ::int64_t;

int brut(int n, int N) {
  Primes<int> pr(N);
  int ans = 0;
  for (auto a: pr) {
    for (auto bPtr = upper_bound(pr.begin(), pr.end(), a); bPtr != pr.end(); ++bPtr) {
      for (auto cPtr = upper_bound(pr.begin(), pr.end(), *bPtr); cPtr != pr.end(); ++cPtr) {
        if (1ll * a * a * *bPtr * *cPtr * *cPtr <= n) {
          ++ans;
        }
      }
    }
  }
  return ans;
}

void solve() {
  i64 n;
  cin >> n;

  Primes<int> prx(1e6 + 10);
  Primes<int> pr(1e4 + 10);

  vector<i64> sq;
  sq.reserve(1e5);
  for (auto p : prx) {
    if (1ll * p * p > n) break ;
    sq.emplace_back(1ll * p * p);
  }

  int ans = 0;
  for (auto a : pr) {
    for (auto bPtr = upper_bound(pr.begin(), pr.end(), a); bPtr != pr.end(); ++bPtr) {
      auto aab = 1ll * a * a * *bPtr;
      auto hi = upper_bound(sq.begin(), sq.end(), n / aab) - sq.begin();
      if (hi == 0) break;
      auto lo = lower_bound(sq.begin(), sq.end(), 1ll * (*bPtr + 1) * (*bPtr + 1)) - sq.begin();
      ans += max(0, int(hi - lo));
    }
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
