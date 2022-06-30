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

    ll n, m; cin >> n >> m;
    multiset<ll> H;
    for (ll i = 0; i < n; ++i) {
        ll h; cin >> h;
        H.insert(h);
    }

    for (ll i = 0; i < m; ++i) {
        ll t; cin >> t;

        auto lb = H.lower_bound(t);
        if (*lb == t) {
            cout << *lb << '\n';
            H.erase(lb);
        } else {
            if (lb == H.begin()) cout << -1 << '\n';
            else {
                auto prev_ = prev(lb);
                cout << *prev_ << '\n';
                H.erase(prev_);
            }
        }
    }

    return 0;
}