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

    read(ll, n);
    if (n == 1) {
        cout << 1 << '\n';
        return 0;
    }

    set<ll> children;
    rep (i, 1, n + 1) {
        children.insert(i);
    }

    auto it = children.begin();
    while (!children.empty()) {
        if (next(it) != children.end()) it = next(it);
        else it = children.begin();

        auto next_ = next(it);
        cout << *it << ' ';
        children.erase(it);
        it = next_;
        if (it == children.end()) it = children.begin();
    }

    return 0;
}