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
    vector<pll> m; m.reserve(n);
    for (ll i = 0; i < n; ++i) {
        ll s_, e_; cin >> s_ >> e_;
        m.eb(e_, s_);
    }

    sort(m.begin(), m.end());

    ll ans = 0, end = 0;
    for (const auto [e_, s_] : m) {
        if (s_ >= end) {
            ++ans;
            end = e_;
        }
    }

    cout << ans << '\n';
    return 0;
}