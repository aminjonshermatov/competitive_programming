#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

typedef long long ll;
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

void solve() {
    ll N, V;
    cin >> N >> V;

    vector<array<ll, 3>> A(N);

    rep (i, 1, N + 1) {
        cin >> A[i - 1][1] >> A[i - 1][0];
        A[i - 1][2] = i;
    }

    sort(A.begin(), A.end(), [](auto &l, auto &r) { return l[0] * r[1] > r[0] * l[1]; });
//    forr (a, A) cout << a[0] << ' ' << a[1] << '\n';
//    cout << '\n';

    vector<ll> res;
    ll ans = 0;
    for (auto &r : A) {
        if (V - r[1] < 0) continue;
        res.push_back(r[2]);
        ans += r[0];
        V -= r[1];
        if (V == 0) break;
    }

    cout << ans << '\n';
    forr(a, res) cout << a << ' ';
    cout << '\n';
}

bool is_multi = false;

int main() {
    // auto start = chrono::steady_clock::now();}

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