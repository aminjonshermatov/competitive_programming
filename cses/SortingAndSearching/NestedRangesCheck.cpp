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

#define IOS ios_base::sync_with_stdio(false); \
            cin.tie(nullptr);                 \
            cout.tie(nullptr);

using namespace std;

int main() {
    IOS

    read(ll, n);
    vector<pll> res(n, mk(0, 0));
    map<pll, ll> r;
    rep(i, 0, n) {
        read(ll, x);
        read(ll, y);
        r[mk(x, y)] = i;
    }

    for (auto it = r.begin(); it != r.end();) {
        auto n_ = next(it);
        while (n_ != r.end() && n_->f.f >= it->f.f && n_->f.s <= it->f.s) {
            res[it->s].f = 1;
            res[n_->s].s = 1;
            n_ = next(n_);
        }
        it = n_;
    }

    rep(i, 0, n) cout << res[i].f << ' ';
    cout << '\n';
    rep(i, 0, n) cout << res[i].s << ' ';
    cout << '\n';
    return 0;
}