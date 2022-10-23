#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

#define F first
#define S second
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
const ll MOD = 1e9 + 7;
[[maybe_unused]] const ld pi = atan2(0, -1);
const ld eps = 1e-6;

// ========================================= PROBLEM =========================================

const ll nax = 5e3;

V<ll> G[nax];
V<bool> used, used2;

void dfs(ll v, ll p) {
    used[v] = true;

    forr(u, G[v]) if (u != p && !used[u]) {
        dfs(u, v);
    }
}

ll dfs2(ll v, ll p) {
    used2[v] = true;
    ll ans = 1;
    forr(u, G[v]) if (u != p && !used2[u]) {
        ans += dfs2(u, v);
    }

    return ans;
}

void solve() {
    ll N, M, s;
    cin >> N >> M >> s;

    used.assign(N, false);

    rep(_, 0, M) {
        ll p, q;
        cin >> p >> q;
        --p, --q;

        G[p].pb(q);
    }

    dfs(--s, -1);

    V<P<ll, ll>> A;
    rep(v, 0, N) if (!used[v]) {
        used2 = used;
        A.pb(mp(dfs2(v, -1), v));
    }

    ll ans = 0;
    sort(rall(A));
    for (auto [_, v] : A) {
        if (!used[v]) dfs(v, -1), ++ans;
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
