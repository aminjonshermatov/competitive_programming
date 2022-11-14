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
const ll MOD = 1e9 + 7;
[[maybe_unused]] const ld pi = atan2(0, -1);
const ld eps = 1e-6;

// ========================================= PROBLEM =========================================

void solve() {
    int N; cin >> N;

    if (N < 2) { cout << "No"; return; }

    int h = N >> 1;
    vector<int> A, B;
    if (N & 1) {
        for (int i = 2; i <= N; i += 2) A.eb(i);
        for (int i = 1; i <= N; i += 2) B.eb(i);
    } else {
        if (h % 1) {
            A.eb(3);
            for (int i = 1; i <= N; ++i) if (i != 3) B.eb(i);
        } else {
            for (int i = 2; i <= N; i += 2) A.eb(i);
            for (int i = 1; i <= N; i += 2) B.eb(i);
        }
    }

    if (__gcd(accumulate(all(A), 0), accumulate(all(B), 0)) == 1) {
        cout << "No\n";
    } else {
        cout << "Yes\n";
        cout << sz(A) << ' ';
        forr(a, A) cout << a << ' ';
        cout << '\n';
        cout << sz(B) << ' ';
        forr(a, B) cout << a << ' ';
        cout << '\n';
    }
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
