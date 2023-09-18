#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = ::int64_t;
using ld = long double;

inline constexpr int  inf = 1e9;
inline constexpr auto ninf = numeric_limits<int>::min();

using pii = pair<int, int>;

void solve() {
    int n; cin >> n;
    vector<int> A(n + 1);
    for (int i = 1; i <= n; ++i) cin >> A[i];
    vector<vector<int>> memo(n + 1, vector<int>(n + 1, -1));

    auto dp = [&](auto f, int day, int coupon) -> int {
      if (coupon > day) return inf;
      int ans;
      if (coupon <= 0) {
          if (day < 1) return 0;
          if (A[day] > 100) return f(f, day - 1, coupon + 1);
          ans = min(f(f, day - 1, coupon + 1), f(f, day - 1, coupon) + A[day]);
      } else {
          if (memo[day][coupon] != -1) return memo[day][coupon];
          if (A[day] > 100) {
              ans = min(f(f, day - 1, coupon + 1), f(f, day - 1, coupon - 1) + A[day]);
          } else {
              ans = min(f(f, day - 1, coupon + 1), f(f, day - 1, coupon) + A[day]);
          }
      }
      return memo[day][coupon] = ans;
    };

    int ans = inf, k1, k2;
    for (int k = 0; k <= n; ++k) {
        auto x = dp(dp, n, k);
        if (x <= ans) {
            ans = x;
            k1 = k;
        }
    }

    vector<int> days;
    days.reserve(k1);
    auto get_path = [&](auto f, int day, int coupon) -> void {
      if (coupon >= day) return;
      if (coupon <= 0) {
          if (day < 1) return;
          if (A[day] > 100) {
              days.emplace_back(day);
              f(f, day - 1, coupon + 1);
          } else {
              if (dp(dp, day - 1, coupon + 1) == dp(dp, day, coupon)) {
                  days.emplace_back(day);
                  f(f, day - 1, coupon + 1);
              } else f(f, day - 1, coupon);
          }
      } else {
          if (A[day] > 100) {
              if (dp(dp, day - 1, coupon + 1) == dp(dp, day, coupon)) {
                  days.emplace_back(day);
                  f(f, day - 1, coupon + 1);
              } else f(f, day - 1, coupon - 1);
          } else {
              if (dp(dp, day - 1, coupon + 1) == dp(dp, day, coupon)) {
                  days.emplace_back(day);
                  f(f, day - 1, coupon + 1);
              } else f(f, day - 1, coupon);
          }
      }
    };

    get_path(get_path, n, k1);
    k2 = int(days.size());
    cout << ans << '\n' << k1 << ' ' << k2 << '\n';
    reverse(days.begin(), days.end());
    for (auto day : days) cout << day << ' ';
    cout << '\n';
}

//#define TIME

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

#ifdef TIME
    auto start = chrono::steady_clock::now();
#endif

    int t = 1;
    //cin >> t;
    while (t--) solve();

#ifdef TIME
    auto finish = chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(finish - start);
    cerr << endl << "Time: " << elapsed_ms.count() << " ms\n";
#endif
}