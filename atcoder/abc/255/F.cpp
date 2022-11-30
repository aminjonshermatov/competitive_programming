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
    int n; cin >> n;

    vector<ll> P(n), L(n);
    map<ll, ll> lidx;

    forr(p, P) cin >> p;
    rep(i, 0, n) cin >> L[i], lidx[L[i]] = i;

    map<ll, pii> ans;
    bool ok = true;
    auto build = [&](auto &self, ll pl, ll pr, ll il, ll ir) -> ll {
        if (pl >= pr || il >= ir) return 0;
        ll root = P[pl];
        ll pos = lidx[root] - il;
        if (pos < 0 || pos + il >= ir) { return ok = false, -1; }
        //cout << l + 1 << ' ' << l + pos << ' ' << l + pos + 1 << ' ' << r << '\n';
        ans[root] = mp(self(self, pl + 1, pl + 1 + pos, il, il + pos), self(self, pl + 1 + pos, pr, il + pos + 1, ir));
        return root;
    };

    build(build, 0, n, 0, n);
    if (ans[1] == mp(0,0) || !ok) { cout << -1; return; }
    rep(i, 1, n + 1) {
        if (auto it = ans.find(i); it == ans.end()) cout << "0 0\n";
        else cout << it->se.fi << ' ' << it->se.se << '\n';
    }
    //for (auto [k, v] : ans) cout << k << ' ' << v.fi << ' ' << v.se << '\n';
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
