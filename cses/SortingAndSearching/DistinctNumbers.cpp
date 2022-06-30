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

    ll n; cin >> n;
    set<ll> s;
    for (int i = 0; i < n; ++i) {
        ll x; cin >> x;
        s.insert(x);
    }
    cout << s.size() << '\n';

    return 0;
}