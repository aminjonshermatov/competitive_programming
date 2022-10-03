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
    ll N, v;
    cin >> N >> v;

    V<pair<ll, ll>> A, B;
    rep(i, 0, N) {
        read(t);
        read(vv);
        if (t == 1) A.emplace_back(vv, i + 1);
        else B.emplace_back(vv, i + 1);
    }

    sort(A.rbegin(), A.rend());
    sort(B.rbegin(), B.rend());

    V<ll> pfA, pfB;
    pfA.reserve(A.size() + 1);
    pfA.emplace_back(0);
    pfB.reserve(B.size() + 1);
    pfB.emplace_back(0);
    forr(a, A) pfA.emplace_back(a.F + pfA.back());
    forr(b, B) pfB.emplace_back(b.F + pfB.back());

//    forr(a, pfA) cout << a << ' ';
//    cout << '\n';
//    forr(a, pfB) cout << a << ' ';
//    cout << '\n';

    ll ans = 0, ans_a = 0, ans_b = 0;
    for (ll i = min(sz(A), v); i >= 0; --i) {
        auto j = min(sz(B), (v - i) / 2);
        auto cur = pfA[i] + pfB[j];
        if (cur > ans) {
            ans = cur;
            ans_a = i;
            ans_b = j;
        }
    }

    cout << ans << '\n';
    rep(i, 0, ans_a) cout << A[i].S << ' ';
    rep(i, 0, ans_b) cout << B[i].S << ' ';
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