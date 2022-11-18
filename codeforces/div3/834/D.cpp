#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;
using namespace __gnu_pbds;

typedef long long           ll;
typedef long double         ld;
typedef pair<ll, ll>        pll;
typedef pair<int, int>      pii;
typedef pair<ll, int>       pli;
typedef pair<int, ll>       pil;
typedef unsigned long long  ull;

#define fi      first
#define se      second
#define P       pair
#define mp      make_pair
#define pb      push_back
#define eb      emplace_back
#define all(x)  (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x)   (ll)((x).size())

#define rep(i, a, b)    for (auto i = (a); (i) < (b); ++(i))
#define forr(el, cont)  for (auto &(el) : (cont))
#define read(k)         ll k; cin >> k

template<typename T = ll> using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

const ll inf = 1e15;
const ll MOD = 1e9 + 7;
const ld pi = atan2(0, -1);
const ld eps = 1e-6;

ull binpow(ll x, ll p) {
    ull ans = 1;
    while (p > 0) {
        if (p & 1) ans *= x;
        x *= x;
        p >>= 1;
    }
    return ans;
}

pair<int, int> get(ll x) {
    pair<int, int> res{0,0};
    for (ll k = x; k % 2 == 0; ++res.fi, k >>= 1) {}
    for (ll k = x; k % 5 == 0; ++res.se, k /= 5) {}
    return res;
}

array<pii, 10> A;

void solve() {
    ll n, m;
    cin >> n >> m;

    pair<int, int> init = get(n);

    pair<int, ll> ans{min(init.fi, init.se), n};
    rep(i, 0, 30) {
        rep(j, 0, 13) {
            ull k = (1 << i) * binpow(5, j);
            for (int x = 1; x < 10 && x * k <= m; ++x) {
                int z = min(i + init.fi + A[x].fi, j + init.se + A[x].se);
                if (z == ans.fi) {
                    //cout << "z=" << z << ' ' << k << ' ' << x << '\n';
                    ans.se = max(ans.se, ll(k * n * x));
                } else if (z > ans.fi) {
                    //cout << "zz=" << z << ' ' << k << ' ' << x << '\n';
                    ans = {z, k * n * x};
                }
            }
        }
    }
    if (min(init.fi, init.se) == ans.fi) ans.se = n * m;

    cout << ans.se << '\n';
}

bool is_multi = true;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    rep(i, 1, 10) A[i] = get(i);

    int T = 1;
    if (is_multi) cin >> T;
    for (int tc = 1; tc <= T; ++tc) solve();

    return 0;
}
