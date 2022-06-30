#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define f first
#define s second

#define ll int64_t

#define ull uint64_t
#define pll pair<ll, ll>
#define pull pair<ull, ull>

#define all(x) (x).begin(), (x).end()
#define sz(x) (ll)(x.size())
#define mk make_pair
#define pb push_back
#define eb emplace_back

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n; cin >> n;
    vector<pll> C;
    C.reserve(n << 1);
    for (ll i = 0; i < n; ++i) {
        ll l, r; cin >> l >> r;
        C.eb(l, 1);
        C.eb(r, -1);
    }
    sort(all(C));

//    for (const auto [a, b] : C) cout << a << ' ' << b << '\n';

    ll res = 0, sum = 0;
    for (ll i = 0; i < n << 1; ++i) {
        sum += C[i].s;
        res = max(res, sum);
    }

    cout << res << '\n';
    return 0;
}