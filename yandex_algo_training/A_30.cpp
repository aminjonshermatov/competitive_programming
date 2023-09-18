#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = ::int64_t;
using ld = long double;

inline constexpr auto  inf = numeric_limits<int>::max();
inline constexpr auto ninf = numeric_limits<int>::min();

using pii = pair<int, int>;

void solve() {
    int l, n; cin >> l >> n;
    vector<int> C(n);
    for (auto &c : C) cin >> c;

    map<pii, i64> cache;
    auto dp = [&](auto f, int l, int r) -> i64 {
        if (l >= r) return 0;
        if (auto it = cache.find(pii(l, r)); it != cache.end()) return it->second;
        auto start = upper_bound(C.begin(), C.end(), l);
        auto end = upper_bound(C.begin(), C.end(), r);
        i64 cur = inf;
        for (auto it = start; it != end && *it < r; ++it) {
            assert(clamp(*it, l, r) == *it);
            auto temp = r - l + f(f, l, *it) + f(f, *it, r);
            cur = min(cur, temp);
        }

        return cache[pii(l, r)] = cur == inf ? 0 : cur;
    };

    cout << dp(dp, 0, l) << '\n';
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
