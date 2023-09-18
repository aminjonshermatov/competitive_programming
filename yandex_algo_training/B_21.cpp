#include "debug.h"
#include <bits/stdc++.h>

using namespace std;

using i64 = ::int64_t;
using ld = long double;

inline constexpr auto  inf = numeric_limits<int>::max();
inline constexpr auto ninf = numeric_limits<int>::min();

using pii = pair<int, int>;

void solve() {
    int n; cin >> n;
    if (n < 3) {
        cout << (1 << n) << '\n';
        return;
    }

    string cur;
    auto rec = [&](auto f, int k, bool is_suf) -> tuple<i64, i64, i64> {
      if (k == 0) {
          //cout << cur << '\n';
          return tuple(
              1,
              (is_suf ? cur.back() : cur.front()) == '1',
              is_suf
                          ? (cur.size() > 1 ? (cur[cur.size() - 1] == '1' && cur[cur.size() - 2] == '1') : 0)
                          : (cur.size() > 1 ? (cur[0] == '1' && cur[1] == '1') : 0)
          );
      }
      tuple ans(i64(0), i64(0), i64(0));
      for (auto ch : {'0', '1'}) {
            cur.push_back(ch);
            bool has = cur.find("111") != string::npos;
            if (!has) {
                auto [x, y, z] = f(f, k - 1, is_suf);
                get<0>(ans) += x;
                get<1>(ans) += y;
                get<2>(ans) += z;
            }
            cur.pop_back();
        }
        return ans;
    };
    auto lhs = n >> 1;
    auto rhs = n - lhs - 1;
    auto [l1, l2, l3] = rec(rec, lhs, true);
    auto [r1, r2, r3] = rec(rec, rhs, false);
    i64 ans = l1 * r1;
    ans += (l1 - l2) * (r1 - r2);
    ans += (l1 - l2) * (r2 - r3);
    ans += (l2 - l3) * (r1 - r2);

    /*cur.clear();
    auto brut = [&](auto f, int k) -> i64 {
        if (k == 0) return 1;
        i64 ans = 0;
        for (auto ch : {'0', '1'}) {
            cur.push_back(ch);
            bool has = cur.find("111") != string::npos;
            if (!has) ans += f(f, k - 1);
            cur.pop_back();
        }
        return ans;
    };*/

    cout << ans <</* ' ' << brut(brut, n) << */'\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    //cin >> t;
    while (t--) solve();
}