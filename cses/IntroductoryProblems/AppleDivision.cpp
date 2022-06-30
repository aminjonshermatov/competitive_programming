#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define ull int64_t

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ull n; cin >> n;
    vector<ull> P(n);
    for (auto &p : P) cin >> p;

    ull sum = accumulate(P.begin(), P.end(), 0ll);

    ull res = INT_MAX;
    function<void(ull, ull)> b = [&](ull cur_, ull idx) {
        if (idx >= P.size()) {
//            cout << sum << ' ' << cur_ << '\n';
            res = min(res, abs(2 * cur_ - sum));
            return;
        }

        for (ull i = idx; i < n; ++i) b(cur_ + P[i], i + 1);
    };

    b(0, 0);

    cout << res << '\n';
    return 0;
}