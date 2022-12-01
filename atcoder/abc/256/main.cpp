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
const ll MOD = 998244353;
const ld pi = atan2(0, -1);
const ld eps = 1e-6;

void solve() {
    int n, q;
    cin >> n >> q;

    vector<ll> A(n + 1, 0), B(n + 1, 0), C(n + 1, 0), D(n + 1, 0);
    auto upd = [&](vector<ll> &cont, int i, ll v) -> void {
        for (; i <= n; i += i & -i) cont[i] += v, cont[i] %= MOD;
    };

    auto sum = [&](vector<ll> &cont, int i) -> ll {
        ll res = 0;
        for (; i > 0; i -= i & -i) res += cont[i], res %= MOD;
        return res;
    };
    rep(i, 1, n + 1) {
        int x; cin >> x;
        upd(A, i, x);
        upd(B, i, sum(A, i));
        upd(C, i, sum(B, i));
        upd(D, i, sum(C, i));
    }

    rep(_, 0, q) {
        char cmd; cin >> cmd;

        if (cmd == '1') {
            int x, v; cin >> x >> v;
            upd(A, x,         v - sum(A, x) + sum(A, x - 1));
            cout << "A " << sum(A, x) - sum(B, x) + sum(B, x - 1) << '\n';
            upd(B, x, sum(A, x) - sum(B, x) + sum(B, x - 1));
            cout << "B " << sum(B, 1) << ' ' << sum(B, 2) << ' ' << sum(B, 3) << '\n';
            upd(C, x, sum(B, x) - sum(C, x) + sum(C, x - 1));
            upd(D, x, sum(C, x) - sum(D, x) + sum(D, x - 1));
        } else if (cmd == '2') {
            int x; cin >> x;
            rep(i, 1, 4) cout << sum(A, i) << ' ' << sum(B, i) << ' ' << sum(C, i) << ' ' << sum(D, i) << '\n';
            cout << sum(D, x) - sum(D, x - 1) << '\n';
        }
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
