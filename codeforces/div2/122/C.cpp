#include "bits/stdc++.h"

using namespace std;

using ll = long long;

void solve() {
    ll hc, dc, hm, dm, k, w, a;
    cin >> hc >> dc >> hm >> dm >> k >> w >> a;

    function<bool(ll, ll)> aa = [&](ll x, ll y) -> bool {
        ll lhs = hc + a * x - hm;
        ll rhs = dm - dc - y * w;
        cout << x << ' ' << y << ' ' << lhs << '?' << rhs << '\n';
        ll k = rhs == 0 ? 0 : lhs / rhs + static_cast<int>(lhs % rhs > 0);
        return hc + x * a - dm * k >= 0;
    };

    for (ll i = 0; i <= k; ++i) {
        if (aa(k - i, i)) {
            cout << "YES" << '\n';
            return;
        }
    }

    cout << "NO" << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int tc;
    cin >> tc;

    while (tc--) {
        solve();
    }
}

/*
4
25 4
9 20
1 1 10
25 4
12 20
1 1 10
100 1
45 2
0 4 10
9 2
69 2
4 2 7
==============
YES
NO
YES
YES
 */