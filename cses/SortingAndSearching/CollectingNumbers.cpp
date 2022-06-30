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
    map<ull, ull> m;
    for (ull i = 0; i < n; ++i) {
        ull x; cin >> x;
        m[x] = i;
    }

    ull last = 0, ans = 1;
    for (ull i = 1; i <= n; ++i) {
        auto it = m.find(i);
        if (it->s < last) ++ans;
        last = it->s;
    }

    cout << ans << '\n';
    return 0;
}