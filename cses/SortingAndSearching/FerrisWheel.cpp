#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define ll int64_t
#define ull uint64_t

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, x;
    cin >> n >> x;
    vector<ll> P(n);
    for (auto &p : P) cin >> p;

    sort(P.begin(), P.end());

    ll res = n;
    ll lo = 0, hi = n - 1;
    while (lo < hi) {
        if (P[lo] + P[hi] <= x) --res, ++lo;
        --hi;
    }

    cout << res << '\n';
    return 0;
}