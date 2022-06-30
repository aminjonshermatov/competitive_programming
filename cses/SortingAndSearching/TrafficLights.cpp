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

#define rep(i, a, b) for (ll i = (a); i < (b); ++i)
#define read(t, k) t k; cin >> k

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll x, n; cin >> x >> n;
    set<ll> light;
    multiset<ll> len;
    len.insert(x);
    light.insert(0);
    light.insert(x);

    rep (i, 0, n) {
        read(ll, p);
        auto lo = light.lower_bound(p);
        auto up = light.upper_bound(p);

        if (lo != light.begin()) lo = prev(lo);

        auto dis = *up - *lo;
        auto it = len.find(dis);
        if (it != len.end()) len.erase(it);

        len.insert(p - *lo);
        len.insert(*up - p);
        light.insert(p);
        cout << *len.rbegin() << ' ';
    }

    return 0;
}