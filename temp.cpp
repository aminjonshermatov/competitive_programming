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

//void solve() { A
//    ll n, m;
//    cin >> n >> m;
//    rep(i, 0, n) {
//        ll a, b;
//        cin >> a >> b;
//    }
//
//    cout << (m < n ? "YES" : "NO");
//}

//void solve() { B
//    ll n;
//    cin >> n;
//    V<ll> A(n), B(n);
//    forr(a, A) cin >> a;
//    forr(b, B) cin >> b;
//
//    V<ll> id(n);
//    iota(all(id), 0);
//    sort(all(id), [&](auto l, auto r) { return B[l] == B[r] ? A[l] < A[r] : B[l] < B[r]; });
//
//    set<ll> free_;
//    rep(i, 0, n) free_.insert(i);
//
//    ll ans = 0;
//    forr(i, id) {
//        ans += A[i];
//
//        auto lo = free_.lower_bound(i);
//        if (lo != free_.begin() && lo != free_.end()) A[*--lo] += B[i];
//        auto hi = free_.upper_bound(i);
//        if (hi != free_.begin() && hi != free_.end()) A[*hi] += B[i];
//        free_.erase(free_.find(i));
//    }
//
//    cout << ans;
//}

void solve() {
    ll N, M;
    cin >> N >> M;

    rep(i, 0, M) {
        ll a, b;
        cin >> a >> b;
    }

    multiset<ll> ms;

    forr(a, ms) {
        cout << a << '\n';
    }

    cout << (M < N ? "YES" : "NO");
}

bool is_multi = true;

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