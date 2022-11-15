#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long double ld;

#define fi first
#define se second
#define P pair
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (ll)((x).size())

#define rep(i, a, b) for (ll i = (a); (i) < (b); ++(i))
#define forr(el, cont) for (auto &(el) : (cont))
#define read(k) ll k; cin >> k

#define IOS ios_base::sync_with_stdio(false); \
            cin.tie(nullptr);                 \
            cout.tie(nullptr);

template<typename T>
using V = vector<T>;

template<typename T = ll>
using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

[[maybe_unused]] mt19937 rnd(143);

const ll inf = 1e15;
const ll MOD = 998244353;
[[maybe_unused]] const ld pi = atan2(0, -1);
const ld eps = 1e-6;

// ========================================= PROBLEM =========================================

ll binpow(ll a, ll n) {
    ll res = 1;
    while (n > 0) {
        if (n & 1) res *= a, res %= MOD, --n;
        a *= a, a %= MOD;
        n >>= 1;
    }

    return  res;
}

inline ll dist(pii &a, pii &b) {
    return abs(a.fi - b.fi) + abs(a.se - b.se);
}

void solve() {
    int n;
    cin >> n;
    map<int, V<pii>> mm;
    rep(_, 0, n) {
        pii a;
        cin >> a.fi >> a.se;
        mm[max(a.fi, a.se)].eb(a);
    }

    for (auto &[_, cont] : mm) {
        sort(all(cont), [](pii a, pii b) {
            if (a.fi != b.fi) return a.fi < b.fi;
            return a.se > b.se;
        });
    }

    ll ans = 0;
    pii cur{0,0};
    for (auto &[_, cont] : mm) {
        int ss = sz(cont);
        pii &f = cont.front();
        pii &b = cont.back();
        if (dist(cur, f) < dist(cur, b)) {
            for (int i = 0; i < ss; ++i) {
                ans += dist(cur, cont[i]);
                cur = cont[i];
            }
        } else {
            for (int i = ss - 1; i >= 0; --i) {
                ans += dist(cur, cont[i]);
                cur = cont[i];
            }
        }
    }

    cout << ans;
}

bool is_multi = false;

int main() {
    // auto start = chrono::steady_clock::now();

    IOS

    int T = 1;
    if (is_multi) cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        // cout << "Case #" << tc << ": ";
        solve();
        cout << '\n';
    }

    // auto finish = chrono::steady_clock::now();
    // auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(finish - start);
    // cerr << endl << "Time: " << elapsed_ms.count() << " ms\n";

    return 0;
}
