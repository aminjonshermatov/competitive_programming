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
    ll ans = 0, cur = 0, mx = INT_MIN;
    for (int i = 0; i < n; ++i) {
        ll x; cin >> x;
        cur += x;
        mx = max(mx, x);
        ans = max(ans, cur);
        cur = max(ll(0), cur);
    }

    cout << (ans == 0 ? mx : ans) << '\n';
    return 0;
}