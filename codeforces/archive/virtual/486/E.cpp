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
#define mk make_pair
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

ll go(string s, string p) {
    assert(sz(p) == 2);
    ll ii = -1, jj = -1, ans = 0;

    rep(i, 0, sz(s)) if (s[i] == p[1]) jj = i;
    if (jj == -1) return inf;
    while (jj + 1 != sz(s)) {
        swap(s[jj], s[jj + 1]);
        ans++;
        ++jj;
    }

    rep(i, 0, sz(s) - 1) if (s[i] == p[0]) ii = i;
    if (ii == -1) return inf;
    while (ii + 2 != sz(s)) {
        swap(s[ii], s[ii + 1]);
        ++ans;
        ++ii;
    }
    if (s.front() != '0') return ans;

    ll pos = sz(s);
    for (ll i = sz(s) - 3; i >= 0; --i) {
        if (s[i] != '0') pos = i;
    }
    if (pos == inf) return inf;
    return ans + pos;
}

void solve() {
    ull n;
    cin >> n;

    auto s = to_string(n);
    ll ans = min(go(s, "00"), min(go(s, "25"), min(go(s, "50"), go(s, "75"))));
    cout << (ans == inf ? -1 : ans);
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
