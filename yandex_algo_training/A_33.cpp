#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

#define fi      first
#define se      second

using namespace std;

using i64 = ::int64_t;
using ld = long double;

inline constexpr auto  inf = numeric_limits<int>::max();
inline constexpr auto ninf = numeric_limits<int>::min();

using pii = pair<int, int>;

inline constexpr ld eps = 1e-9;

inline i64 get_dist(pii &a, pii &b) {
    auto dx = a.fi - b.fi;
    dx *= dx;
    auto dy = a.se - b.se;
    dy *= dy;
    return dx + dy;
}

void solve() {
    int n; cin >> n;
    vector<pii> Vs(n);
    for (int i = 0; i < n; ++i) cin >> Vs[i].fi >> Vs[i].se;

    vector<int> color(n, 0);
    auto dfs = [&](auto f, int vi, int c, ld r) -> bool {
        color[vi] = c;
        for (int vj = 0; vj < n; ++vj) if (vi != vj && get_dist(Vs[vi], Vs[vj]) <= r * r) {
                if (color[vj] == c || (color[vj] == 0 && !f(f, vj, 3 ^ c, r))) return false;
            }
        return true;
    };
    auto ok = [&](auto r) -> bool {
        fill(color.begin(), color.end(), 0);
        for (int vi = 0; vi < n; ++vi) if (color[vi] == 0) {
            if (!dfs(dfs, vi, 1, r)) {
                return false;
            }
        }
        return true;
    };

    ld lo = 0, hi = 1e9;
    vector<int> cached_color;
    while (hi - lo >= eps) {
        auto mid = lo + (hi - lo) / 2;
        if (ok(mid)) {
            cached_color = color;
            lo = mid;
        } else {
            hi = mid;
        }
    }
    cout << fixed << setprecision(10) << (lo + eps) / 2 << '\n';
    for (auto c : cached_color) cout << c << ' ';
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
