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

    ll n, x; cin >> n >> x;
    map<ll, ll> m;
    for (ll i = 1; i <= n; ++i) {
        ll a; cin >> a;

        auto f_ = m.find(x - a);
        if (f_ != m.end()) {
            cout << f_->s << ' ' << i << '\n';
            return 0;
        }
        m[a] = i;
    }

    cout << "IMPOSSIBLE\n";
    return 0;
}