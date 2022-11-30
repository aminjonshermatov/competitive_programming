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
const ld eps = 1e-7;

void solve() {
    int n, q; cin >> n >> q;

    vector<ll> A(n);
    forr(a, A) cin >> a;
    sort(all(A));
    vector<ll> pf(n + 1, 0);
    rep(i, 0, n) pf[i + 1] = pf[i] + A[i];
    auto sm = accumulate(all(A), 0ll);

    auto sum = [&](ll l, ll r) { return pf[r] - pf[l - 1]; };

    rep(_, 0, q) {
        int x; cin >> x;

        ll l = 0;
        if (auto lo = lower_bound(all(A), x); lo != A.begin()) l = lo - A.begin();
        ll r = n;
        if (auto hi = upper_bound(all(A), x); hi != A.end()) r = hi - A.begin();
        cout << x * l - sum(1, l) + sum(r + 1, n) - x * (n - r) << '\n';
    }
}

bool is_multi = false;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T = 1;
    if (is_multi) cin >> T;
    for (int tc = 1; tc <= T; ++tc) solve();

    return 0;
}
