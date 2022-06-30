#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define f first
#define s second

#define ll      int64_t
#define ull     uint64_t
#define pll     pair<ll, ll>
#define pull    pair<ull, ull>

#define all(x)  (x).begin(), (x).end()
#define sz(x)   (ll)(x.size())
#define mk      make_pair
#define pb      push_back
#define eb      emplace_back

#define rep(i, a, b) for (ll i = (a); i < (b); ++i)
#define read(t, k) t k; cin >> k

#define IOS ios_base::sync_with_stdio(false); \
            cin.tie(nullptr);                 \
            cout.tie(nullptr);

using namespace std;

int main() {
    IOS

    int tc = 1;
    cin >> tc;

    while (tc--) {
        read(ll, n);

        ll m = n / 3;
        ll mod = n % 3 + 1;
        n -= 2*m + mod;
        if (mod == 3) {
            mod -= 2;
            ++m;
        }
        cout << m << ' ' << m + mod << ' ' << n << '\n';
    }

    return 0;
}