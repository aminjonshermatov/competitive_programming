#include <bits/stdc++.h>

using namespace std;

using i64 =  ::int64_t;
using u64 = ::uint64_t;

inline constexpr auto  inf = numeric_limits<int>::max();
inline constexpr auto ninf = numeric_limits<int>::min();

void solve() {
    int k; cin >> k;
    int l = inf, r = ninf, t = ninf, b = inf;
    for (int _ = 0; _ < k; ++_) {
        int x, y; cin >> x >> y;
        l = min(l, x);
        r = max(r, x);
        t = max(t, y);
        b = min(b, y);
    }
    cout << l << ' ' << b << ' ' << r << ' ' << t << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    //cin >> t;
    while (t--) solve();
}