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

    ll n, m, k;
    cin >> n >> m >> k;

    vector<ll>  A(n), B(m);
    for (auto &a : A) cin >> a;
    for (auto &b : B) cin >> b;

    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    ll res = 0, j = 0;
    for (const auto a : A) {
        while (j < m && B[j] + k < a) ++j;
        if (j < m && abs(B[j] - a) <= k) ++res, ++j;
    }

    cout << res << '\n';
    return 0;
}