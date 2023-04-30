// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

// density of primes ~= N/ln(N)
// so M = root of eq.: 10001 = x/lg(x)
constexpr int N = 10'001;
constexpr int M = 120'000;

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

void solve() {
  Primes<int> pr(M);
  cout << pr[N - 1] << '\n';
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
